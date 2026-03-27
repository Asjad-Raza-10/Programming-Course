-- Q1
-- Each LEFT JOIN goes one level up the superssn chain.
-- SUM counts how many of those levels actually exist (are not NULL).
CREATE VIEW v_ManagerDepth
AS
SELECT (d.fname + ' ' + d.lname) AS Doctor_Name, s.sname AS Specialization,
(CASE WHEN s1.ssn IS NOT NULL THEN 1 ELSE 0 END +
 CASE WHEN s2.ssn IS NOT NULL THEN 1 ELSE 0 END +
 CASE WHEN s3.ssn IS NOT NULL THEN 1 ELSE 0 END ) AS Supervisors_Count
FROM doctor d JOIN specialization s
ON d.sno = s.snumber
LEFT JOIN doctor s1
ON d.superssn = s1.ssn
LEFT JOIN doctor s2
ON s1.superssn = s2.ssn
LEFT JOIN doctor s3
ON s2.superssn = s3.ssn;

SELECT * FROM v_ManagerDepth;

-- Q2
CREATE VIEW v_CrossSpecDoctors 
AS
SELECT (d.fname + ' ' + d.lname) AS Doctor_Name, s.sname AS Specialization, COUNT(*) AS Cross_Spec_Surgeries
FROM doctor d JOIN specialization s
ON d.sno = s.snumber
JOIN performed_by pb
ON d.ssn = pb.essn
JOIN surgery srg
ON pb.sno = srg.snumber
WHERE d.sno != srg.snum
GROUP BY d.fname, d.lname, s.sname;

SELECT * FROM v_CrossSpecDoctors;
-- Q3
CREATE VIEW v_InvalidSurgeryLocations
AS
SELECT srg.sname AS Surgery_Name, srg.slocation AS Location, s.sname AS Specialization_Name,
CASE WHEN EXISTS (SELECT 1 FROM spec_locations sl 
WHERE sl.snumber = srg.snum AND sl.slocation = srg.slocation) THEN 'VALID' ELSE 'INVALID' END AS Status
FROM surgery srg JOIN specialization s
ON srg.snum = s.snumber;

SELECT * FROM v_InvalidSurgeryLocations;

-- Q4
CREATE VIEW v_OverloadedManagers
AS
SELECT (mgr.fname + ' ' + mgr.lname) AS Manager_Name, COUNT(DISTINCT sub.ssn) AS Doctors_Supervised, SUM(pb.hours) AS Total_Team_Hours
FROM doctor mgr JOIN doctor sub
ON sub.superssn = mgr.ssn
LEFT JOIN performed_by pb
ON pb.essn = sub.ssn
GROUP BY mgr.ssn, mgr.fname, mgr.lname;

SELECT * FROM v_InvalidSurgeryLocations;

-- Q5
CREATE VIEW v_DependencyBurden
AS
SELECT TOP 100 PERCENT -- because simple order by isnt allowed for views
(d.fname + ' ' + d.lname) AS Doctor_Name, d.salary, COUNT(dp.dependent_name) AS No_of_Dependents
FROM doctor d JOIN dependent dp 
ON d.ssn = dp.essn
GROUP BY d.fname, d.lname, d.salary
ORDER BY (CAST(COUNT(dp.dependent_name) AS FLOAT) / d.salary) DESC;

SELECT * FROM v_InvalidSurgeryLocations;

-- Q6
CREATE PROCEDURE sp_ReassignToBalancedSpec
    @ssn CHAR(9)
AS
BEGIN
    DECLARE @sno INT;
    DECLARE @mgrssn CHAR(9);

    -- Find the specialization with the fewest doctors
    SELECT TOP 1 @sno = d.sno
    FROM doctor d
    GROUP BY d.sno
    ORDER BY COUNT(DISTINCT d.ssn) ASC;

    -- Get the manager of that specific specialization
    SELECT @mgrssn = mgrssn 
    FROM specialization 
    WHERE snumber = @sno;

    -- Update the doctor's record
    UPDATE doctor
    SET sno = @sno, 
        superssn = @mgrssn
    WHERE ssn = @ssn;
END;

SELECT * FROM doctor WHERE ssn = 123456789;
EXEC sp_ReassignToBalancedSpec @ssn = 123456789;
SELECT * FROM doctor WHERE ssn = 123456789;

-- Q7
-- I have learnt to use Cursor which acts like an iterator 
-- to fetch each record one by one to perform operations
-- I fully understand this code and its working
CREATE PROCEDURE sp_RedistributeSurgeryHours
AS
BEGIN
    -- Variables to hold data for the "overloaded" doctor we are currently processing
    DECLARE @essn CHAR(9);
    DECLARE @sno INT;
    DECLARE @hours DECIMAL(4,1);
    DECLARE @reduced_time DECIMAL(4,1);
    DECLARE @other_doctors_count INT;

    -- A Cursor is like a 'foreach' loop for SQL rows
    DECLARE surgery_cursor CURSOR FOR 
        SELECT essn, sno, hours 
        FROM performed_by 
        WHERE hours > 30;

    OPEN surgery_cursor;
    FETCH NEXT FROM surgery_cursor INTO @essn, @sno, @hours;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        -- Calculate the 20% "burden" to move
        SET @reduced_time = @hours * 0.20;

        -- Count how many OTHER doctors are on this specific surgery
        SELECT @other_doctors_count = COUNT(*) 
        FROM performed_by 
        WHERE sno = @sno AND essn != @essn;

        -- Only redistribute if there is actually someone else to give it to
        IF @other_doctors_count > 0
        BEGIN
            -- Reduce the original doctor's hours
            UPDATE performed_by 
            SET hours = hours - @reduced_time
            WHERE essn = @essn AND sno = @sno;

            -- Distribute the time equally to the others
            UPDATE performed_by
            SET hours = hours + (@reduced_time / @other_doctors_count)
            WHERE sno = @sno AND essn != @essn;
        END

        FETCH NEXT FROM surgery_cursor INTO @essn, @sno, @hours;
    END;

    CLOSE surgery_cursor;
    DEALLOCATE surgery_cursor;
END;

SELECT * FROM performed_by;
EXEC sp_RedistributeSurgeryHours;
SELECT * FROM performed_by;

-- Q8
CREATE PROCEDURE sp_FixSupervisorCycles
AS
BEGIN
    DECLARE @ssn CHAR(9);
    
    -- Select doctors who are their own direct supervisor
    DECLARE ssn_cursor CURSOR FOR
        SELECT ssn 
        FROM doctor 
        WHERE ssn = superssn;

    OPEN ssn_cursor;

    FETCH NEXT FROM ssn_cursor INTO @ssn;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        UPDATE doctor
        SET superssn = NULL
        WHERE ssn = @ssn;

        FETCH NEXT FROM ssn_cursor INTO @ssn;
    END;

    CLOSE ssn_cursor;
    DEALLOCATE ssn_cursor;
END;

SELECT * FROM doctor;
EXEC sp_FixSupervisorCycles
SELECT * FROM doctor;

-- Q9
CREATE PROCEDURE sp_ReplaceManager
    @snumber INT,
    @new_mgrssn CHAR(9)
AS
BEGIN
    DECLARE @old_mgrssn CHAR(9);

    -- Get the current (old) manager SSN for this specialization
    SELECT @old_mgrssn = mgrssn 
    FROM specialization 
    WHERE snumber = @snumber;

    -- Verify the new manager actually belongs to this specialization
    -- This prevents assigning a Pediatrician to manage Orthopedics, for example.
    IF EXISTS (SELECT 1 FROM doctor WHERE ssn = @new_mgrssn AND sno = @snumber)
    BEGIN
        -- Update the Specialization table
        UPDATE specialization
        SET mgrssn = @new_mgrssn,
            mgrstartdate = GETDATE()
        WHERE snumber = @snumber;

        -- Update the Doctor table (Subordinates)
        -- Update superssn only for doctors in this specific specialization 
        -- who used to report to the old manager.
        UPDATE doctor
        SET superssn = @new_mgrssn
        WHERE sno = @snumber 
          AND superssn = @old_mgrssn;
    END
END;

SELECT * FROM specialization;
EXEC sp_ReplaceManager @snumber = 2, @new_mgrssn = 987654321;
SELECT * FROM specialization;

-- Q10
CREATE PROCEDURE sp_DeleteDoctorCascade
    @ssn_to_delete CHAR(9)
AS
BEGIN
    DECLARE @supervisor_ssn CHAR(9);
    DECLARE @specialization_id INT;
    DECLARE @backup_doctor_ssn CHAR(9);

    -- Get the doctor's current supervisor and specialization
    SELECT @supervisor_ssn = superssn, @specialization_id = sno 
    FROM doctor 
    WHERE ssn = @ssn_to_delete;

    -- Reassign Dependents to the doctor's supervisor
    UPDATE dependent
    SET essn = @supervisor_ssn
    WHERE essn = @ssn_to_delete;

    -- Find a backup doctor for surgeries (someone in the same specialization)
    SELECT TOP 1 @backup_doctor_ssn = ssn 
    FROM doctor 
    WHERE sno = @specialization_id AND ssn <> @ssn_to_delete;

    IF @backup_doctor_ssn IS NOT NULL
    BEGIN
        UPDATE performed_by
        SET essn = @backup_doctor_ssn, hours = 0 -- reset hours for new doc
        WHERE essn = @ssn_to_delete;
    END

    -- Replace them if they are a Manager of a specialization
    -- I am using the backup doctor found above to take over the department
    IF @backup_doctor_ssn IS NOT NULL
    BEGIN
        UPDATE specialization
        SET mgrssn = @backup_doctor_ssn,
            mgrstartdate = GETDATE()
        WHERE mgrssn = @ssn_to_delete;
    END

    -- 5. Finally delete the doctor now
    DELETE FROM doctor 
    WHERE ssn = @ssn_to_delete;

    -- syntax to print a message on screen
    PRINT 'Doctor ' + @ssn_to_delete + ' deleted and responsibilities reassigned.';
END;

SELECT * FROM doctor;
EXEC sp_DeleteDoctorCascade @ssn_to_delete = 112233445;
SELECT * FROM doctor;
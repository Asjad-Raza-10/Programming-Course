-- Q1
BEGIN TRANSACTION;
BEGIN TRY
    INSERT INTO match VALUES (206, '2025-04-01', 'Multan', 1, 4, 1, 2);
    INSERT INTO performance VALUES (101, 206, 45, 0, 1);
    INSERT INTO performance VALUES (102, 206, 5, 2, 0);
    COMMIT;
    PRINT 'Committed.';
END TRY
BEGIN CATCH
    ROLLBACK;
    PRINT 'Rolled back: ' + ERROR_MESSAGE();
END CATCH

-- Q2
BEGIN TRANSACTION;
BEGIN TRY
    UPDATE player SET tid = 2 WHERE pid = 105;
    UPDATE player SET captain_id = NULL WHERE captain_id = 105;
    COMMIT;
    PRINT 'Committed.';
END TRY
BEGIN CATCH
    ROLLBACK;
    PRINT 'Rolled back: ' + ERROR_MESSAGE();
END CATCH

-- Q3
BEGIN TRANSACTION;
DECLARE @t1 INT = 1, @t2 INT = 4;
IF EXISTS (SELECT 1 FROM team WHERE tid = @t1)
   AND EXISTS (SELECT 1 FROM team WHERE tid = @t2)
BEGIN
    INSERT INTO match VALUES (207, '2025-05-01', 'Lahore', @t1, @t2, @t1, 2);
    COMMIT;
    PRINT 'Committed.';
END
ELSE
BEGIN
    ROLLBACK;
    PRINT 'Rolled back: one or both teams do not exist.';
END


-- Q4
BEGIN TRANSACTION;
BEGIN TRY
    INSERT INTO tournament VALUES (11, 'Asjads League', 2026);
    SAVE TRANSACTION sp1;
    INSERT INTO match VALUES (225, '2026-01-01', 'Karachi', 1, 2, 1, 11);
    INSERT INTO match VALUES (226, '2026-01-05', 'Lahore', 3, 4, 3, 11);
    COMMIT;
    PRINT 'Committed: tournament and matches saved.';
END TRY
BEGIN CATCH
    ROLLBACK TRANSACTION sp1;
    PRINT 'Rolled back to savepoint: invalid teams in matches.';
    COMMIT;
    PRINT 'Committed: tournament saved.';
END CATCH

-- Q5
BEGIN TRANSACTION;
UPDATE player SET salary = salary * 1.10 WHERE tid = 1;
IF (SELECT AVG(salary) FROM player WHERE tid = 1) > 90000
BEGIN
    ROLLBACK;
    PRINT 'Rolled back: average salary exceeds 90000.';
END
ELSE
BEGIN
    COMMIT;
    PRINT 'Committed.';
END

-- Q6
BEGIN TRANSACTION;
INSERT INTO performance VALUES (101, 208, 510, 0, 1);
IF (SELECT SUM(runs) FROM performance WHERE mid = 208) > 500
BEGIN
    ROLLBACK;
    PRINT 'Rolled back: total runs exceed 500.';
END
ELSE
BEGIN
    COMMIT;
    PRINT 'Committed.';
END

-- Q7
BEGIN TRANSACTION;
INSERT INTO team VALUES ('Sialkot Stallions', 8, 'Moin Khan', 'Sialkot');
SAVE TRANSACTION sp1;
INSERT INTO player VALUES ('Kamran Akmal', 114, 38, 'Wicketkeeper', 60000, 8, NULL);
INSERT INTO player VALUES ('Umar Akmal', 115, 33, 'Batsman', -5000, 8, 114);
INSERT INTO player VALUES ('Adnan Akmal', 116, 35, 'Batsman', 55000, 8, 114);
IF EXISTS (SELECT 1 FROM player WHERE tid = 8 AND salary < 0)
BEGIN
    ROLLBACK TRANSACTION sp1;
    PRINT 'Rolled back to savepoint: invalid player data.';
END
COMMIT;
PRINT 'Committed: team insert saved.';

SELECT * FROM team;
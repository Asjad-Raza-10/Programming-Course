-- =============================================
-- PART 1: Nested Queries & Aggregations
-- =============================================

-- 1. Patients infected with 'Dartu Virus' using subquery
SELECT Name
FROM Patients
WHERE PatientID IN (
    SELECT PatientID
    FROM Infections
    WHERE GermID = (
        SELECT GermID
        FROM Germs
        WHERE Name = 'Dartu Virus'
    )
);
GO


-- =============================================
-- PART 2: Views
-- =============================================

-- 1. View for high impact germs (ImpactLevel >= 8)
CREATE VIEW vw_HighImpactGerms AS
SELECT *
FROM Germs
WHERE ImpactLevel >= 8;
GO

-- Test it
SELECT * FROM vw_HighImpactGerms;
GO


-- =============================================
-- PART 3: Stored Procedures
-- =============================================

-- 1. Stored procedure to add a new patient
CREATE PROCEDURE sp_AddPatient
    @Name   NVARCHAR(100),
    @Age    INT,
    @Gender NVARCHAR(10)
AS
BEGIN
    INSERT INTO Patients (Name, Age, Gender)
    VALUES (@Name, @Age, @Gender);
END;
GO

-- Test it
EXEC sp_AddPatient @Name = 'Zara Malik', @Age = 27, @Gender = 'Female';
GO


-- =============================================
-- PART 4: Triggers
-- =============================================

-- 1. Audit trigger — fires AFTER INSERT on Prescriptions
CREATE TRIGGER tr_AuditPrescriptions
ON Prescriptions
AFTER INSERT
AS
BEGIN
    INSERT INTO Prescriptions_History (PrescriptionID, PatientID, PrescriptionDate, ValidFrom)
    SELECT
        PrescriptionID,
        PatientID,
        PrescriptionDate,
        GETDATE()
    FROM inserted;
END;
GO

-- Test it (trigger fires automatically)
SELECT * FROM Prescriptions_History;
GO

INSERT INTO Prescriptions (PatientID, PrescriptionDate)
VALUES (1, GETDATE());
GO

SELECT * FROM Prescriptions_History;
GO


-- =============================================
-- PART 5: Transactions
-- =============================================

-- 1. Insert a Prescription + 2 Prescription_Remedies atomically
BEGIN TRANSACTION;
BEGIN TRY

    -- Step 1: Insert the prescription
    INSERT INTO Prescriptions (PatientID, PrescriptionDate)
    VALUES (2, GETDATE());

    -- Grab the new PrescriptionID
    DECLARE @NewPrescriptionID INT = SCOPE_IDENTITY();

    -- Step 2: Insert first remedy
    INSERT INTO Prescription_Remedies (PrescriptionID, RemedyID, Dosage)
    VALUES (@NewPrescriptionID, 1, 'Once daily');

    -- Step 3: Insert second remedy
    INSERT INTO Prescription_Remedies (PrescriptionID, RemedyID, Dosage)
    VALUES (@NewPrescriptionID, 2, 'Twice daily');

    COMMIT TRANSACTION;
    PRINT 'Transaction committed successfully.';

END TRY
BEGIN CATCH

    ROLLBACK TRANSACTION;
    PRINT 'Error occurred — transaction rolled back.';
    PRINT ERROR_MESSAGE();

END CATCH;
GO
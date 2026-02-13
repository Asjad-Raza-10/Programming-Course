-- Q1
CREATE TABLE Patient(
PatientID int IDENTITY(1,1) PRIMARY KEY,
Name varchar(15) NOT NULL,
Age int,
CHECK (Age>5),
Gender varchar(5),
Address varchar(20),
Disease varchar(10),
DoctorID varchar(15)
)

-- Q2
ALTER TABLE Patient
ALTER COLUMN Gender char;

-- Q3
CREATE TABLE Doctor(
DoctorID int IDENTITY(1,1) PRIMARY KEY,
Name varchar (15) NOT NULL,
Age int,
CHECK (Age>18),
Gender char,
Address varchar(20)
)

-- Q4
ALTER TABLE Doctor
ADD DrSpecialization varchar(20)

-- Q5
ALTER TABLE Patient
ALTER COLUMN DoctorID int;

ALTER TABLE Patient
ADD CONSTRAINT FK_DoctorID
FOREIGN KEY (DoctorID)
REFERENCES Doctor(DoctorID);

-- Q6
CREATE TABLE LabTest(
LabID int IDENTITY(1,1) PRIMARY KEY,
LabNo varchar(10) UNIQUE,
TestDate date DEFAULT GETDATE(),
TestAmount float,
PatientID int REFERENCES Patient(PatientID),
DoctorID int REFERENCES Doctor(DoctorID)
)

-- Q7
CREATE TABLE PatientBill(
BillID int IDENTITY(1,1) PRIMARY KEY,
BillDate date DEFAULT GETDATE(),
Amount varchar(20),
PatientID int REFERENCES Patient(PatientID),
DoctorID int REFERENCES Doctor(DoctorID)
)

-- Q8
DROP TABLE LabTest;

-- Q9
INSERT INTO Doctor (Name, Age, Gender, Address, DrSpecialization)
VALUES
('Asjad', 19, 'M', 'Karachi', 'Neuro Surgeon'),
('Ali', 19, 'M', 'Lahore', 'General Physician'),
('Rehan', 19, 'M', 'Islamabad', 'Cardio'),
('Shaheer', 20, 'M', 'Peshawar', 'Radiology');

-- Q10
INSERT INTO Patient (Name, Age, Gender, Address, Disease, DoctorID)
VALUES
('Momin', 25, 'M', 'Karachi', 'Flu', 1),
('Saood', 30, 'M', 'Lahore', 'Fever', 2),
('Dawar', 20, 'M', 'Islamabad', 'Cough', 3),
('Abdullah', 15, 'M', 'Peshawar', 'Allergy', 4);

-- Q11
INSERT INTO PatientBill (Amount, PatientID, DoctorID)
VALUES
('1500', 1, 1),  -- Bill for Momin with Doctor Asjad
('2000', 2, 2);  -- Bill for Saood with Doctor Ali

-- Q12
SELECT *
FROM Doctor

SELECT *
FROM Patient

SELECT * 
FROM PatientBill
WHERE Amount > 100;

-- Q13
DELETE FROM PatientBill;

-- Q14
DELETE FROM Patient
WHERE Name = 'Dawar';

-- Q15
UPDATE Patient
SET Disease = 'Covid'
WHERE Disease = 'Flu';
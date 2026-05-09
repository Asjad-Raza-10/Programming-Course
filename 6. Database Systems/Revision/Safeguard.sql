-- 1. Create Database
CREATE DATABASE Safegaurd;
GO
USE Safegaurd;
GO

-- 2. Germs Table 
CREATE TABLE Germs (
    GermID INT IDENTITY(1,1) PRIMARY KEY,
    Name NVARCHAR(100) NOT NULL,
    Role NVARCHAR(50) CHECK (Role IN ('Airborne', 'Waterborne', 'Contact-Based', 'Other')),
    ImpactLevel INT CHECK (ImpactLevel BETWEEN 1 AND 10),
    DiscoveredDate DATE
);
GO

-- 3. Patients Table
CREATE TABLE Patients (
    PatientID INT IDENTITY(1,1) PRIMARY KEY,
    Name NVARCHAR(100) NOT NULL,
    Age INT CHECK (Age > 0),
    Gender NVARCHAR(10) CHECK (Gender IN ('Male', 'Female', 'Other'))
);
GO

-- 4. Locations Table
CREATE TABLE Locations (
    LocationID INT IDENTITY(1,1) PRIMARY KEY,
    Name NVARCHAR(100) NOT NULL,
    Latitude FLOAT,
    Longitude FLOAT,
    InfectionStatus BIT DEFAULT 0
);
GO

-- 5. Infections Table (Tracks which patient is infected with which germ)
CREATE TABLE Infections (
    InfectionID INT IDENTITY(1,1) PRIMARY KEY,
    PatientID INT REFERENCES Patients(PatientID) ON DELETE CASCADE,
    GermID INT REFERENCES Germs(GermID) ON DELETE CASCADE,
    InfectionDate DATETIME2 NOT NULL DEFAULT GETDATE(),
    RecoveryDate DATETIME2 NULL
);
GO

-- 6. Germ_Locations Table (Tracks where germs are found separately)
CREATE TABLE Germ_Locations (
    GermID INT REFERENCES Germs(GermID) ON DELETE CASCADE,
    LocationID INT REFERENCES Locations(LocationID) ON DELETE CASCADE,
    PRIMARY KEY (GermID, LocationID)
);
GO

-- 7. Remedies Table 
CREATE TABLE Remedies (
    RemedyID INT IDENTITY(1,1) PRIMARY KEY,
    Name NVARCHAR(100) NOT NULL,
    Description NVARCHAR(255),
    EffectivenessLevel INT CHECK (EffectivenessLevel BETWEEN 1 AND 10)
);
GO

-- 8. Prescriptions Table (A prescription can have multiple remedies)
CREATE TABLE Prescriptions (
    PrescriptionID INT IDENTITY(1,1) PRIMARY KEY,
    PatientID INT REFERENCES Patients(PatientID) ON DELETE CASCADE,
    PrescriptionDate DATETIME2 NOT NULL DEFAULT GETDATE()
);
GO

-- 9. Prescription_Remedies Table (Stores multiple remedies per prescription)
CREATE TABLE Prescription_Remedies (
    PrescriptionID INT REFERENCES Prescriptions(PrescriptionID) ON DELETE CASCADE,
    RemedyID INT REFERENCES Remedies(RemedyID) ON DELETE CASCADE,
    Dosage NVARCHAR(50) NOT NULL,
    PRIMARY KEY (PrescriptionID, RemedyID)
);
GO

-- 10. Weapons Table
CREATE TABLE Weapons (
    WeaponID INT IDENTITY(1,1) PRIMARY KEY,
    Name NVARCHAR(100) NOT NULL,
    Type NVARCHAR(50) CHECK (Type IN ('Chemical', 'Mechanical', 'Biological')),
    EffectivenessLevel INT CHECK (EffectivenessLevel BETWEEN 1 AND 10)
);
GO

-- 11. Weapon_Germs Table (Tracks which weapons target which germs)
CREATE TABLE Weapon_Germs (
    WeaponID INT REFERENCES Weapons(WeaponID) ON DELETE CASCADE,
    GermID INT REFERENCES Germs(GermID) ON DELETE CASCADE,
    PRIMARY KEY (WeaponID, GermID)
);
GO

-- 12. Prescriptions_History Table (Temporal Data for Prescriptions)
CREATE TABLE Prescriptions_History (
    PrescriptionID INT,
    PatientID INT,
    PrescriptionDate DATETIME2 NOT NULL,
    ValidFrom DATETIME2 NOT NULL DEFAULT GETDATE(),
    ValidTo DATETIME2 NULL
);
GO

PRINT 'Schema Created Successfully!';

-- Insert data into Germs table
INSERT INTO Germs (Name, Role, ImpactLevel, DiscoveredDate) VALUES
('Dartu Virus', 'Airborne', 9, '2024-01-15'),
('Kachra Bacteria', 'Contact-Based', 7, '2023-12-10'),
('Darti Parasite', 'Waterborne', 8, '2024-02-20'),
('Khansana Flu', 'Airborne', 6, '2024-03-05'),
('Toxic Mold', 'Other', 5, '2023-11-25'),
('Jerm Attack', 'Airborne', 8, '2024-02-10'),
('Bacteria Khan', 'Contact-Based', 9, '2023-10-22'),
('Germinator', 'Waterborne', 7, '2024-01-30'),
('Microbe Master', 'Other', 6, '2024-03-12'),
('Contagion King', 'Airborne', 10, '2023-09-15');
GO
-- Insert data into Patients table
INSERT INTO Patients (Name, Age, Gender) VALUES
('Ali Khan', 35, 'Male'),
('Sara Ahmed', 40, 'Female'),
('Usman Tariq', 30, 'Male'),
('Ayesha Iqbal', 45, 'Female'),
('Hamza Sheikh', 38, 'Male');
GO
-- Insert data into Locations table
INSERT INTO Locations (Name, Latitude, Longitude, InfectionStatus) VALUES
('Safe City HQ', 24.8607, 67.0011, 0),
('Dartu’s Hideout', 25.276987, 55.296249, 1),
('Kachra Rani’s Dumpyard', 31.5497, 74.3436, 1),
('Khansana’s Kitchen', 33.6844, 73.0479, 0),
('Darti’s Swamp', 35.6892, 51.3890, 1);
GO
-- Insert data into Infections table
INSERT INTO Infections (PatientID, GermID, InfectionDate, RecoveryDate) VALUES
(2, 1, '2025-03-01', NULL),
(3, 3, '2025-02-15', '2025-03-10'),
(4, 4, '2025-03-05', NULL),
(5, 2, '2025-01-20', '2025-02-20'),
(1, 5, '2025-03-18', NULL);
GO
-- Insert data into Germ_Locations table
INSERT INTO Germ_Locations (GermID, LocationID) VALUES
(1, 2),
(2, 3),
(3, 5),
(4, 4),
(5, 1);
GO
-- Insert data into Remedies table
INSERT INTO Remedies (Name, Description, EffectivenessLevel) VALUES
('Super Soap', 'Eliminates 99% of airborne germs', 10),
('Antiseptic Spray', 'Neutralizes contact-based infections', 8),
('Purity Tablets', 'Cleans water from parasites', 9),
('Flu Vaccine', 'Prevents airborne flu', 7),
('Anti-Mold Shield', 'Removes mold spores', 6);
Go
-- Insert data into Prescriptions table
INSERT INTO Prescriptions (PatientID, PrescriptionDate) VALUES
(1, '2025-03-10'),
(2, '2025-03-05'),
(3, '2025-02-25'),
(4, '2025-03-07'),
(5, '2025-01-30');
Go
-- Insert data into Prescription_Remedies table
INSERT INTO Prescription_Remedies (PrescriptionID, RemedyID, Dosage) VALUES
(1, 1, 'Twice daily'),
(2, 2, 'Once daily'),
(3, 3, 'After every meal'),
(4, 4, 'Weekly injection'),
(5, 5, 'Apply twice a week');
Go
-- Insert data into Weapons table
INSERT INTO Weapons (Name, Type, EffectivenessLevel) VALUES
('Sanitizer Bomb', 'Chemical', 9),
('Ultra Shield', 'Mechanical', 8),
('Bio Purifier', 'Biological', 10),
('Sterile Mist', 'Chemical', 7),
('Anti-Infection Spray', 'Chemical', 6);
Go
-- Insert data into Weapon_Germs table
INSERT INTO Weapon_Germs (WeaponID, GermID) VALUES
(1, 1),
(2, 2),
(3, 3),
(4, 4),
(5, 5);
Go

PRINT 'Data Inserted Successfully!';
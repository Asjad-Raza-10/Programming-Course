CREATE TABLE Employees (
    EmployeeID INT PRIMARY KEY,
    FirstName VARCHAR(50),
    LastName VARCHAR(50),
    Department VARCHAR(50),
    HireDate DATE,
    Salary DECIMAL(10, 2)
);

INSERT INTO Employees (EmployeeID, FirstName, LastName, Department, HireDate, Salary)
VALUES
(1, 'John', 'Doe', 'Sales', '2019-03-15', 50000.00),
(2, 'Jane', 'Smith', 'Marketing', '2018-07-21', 62000.00),
(3, 'Michael', 'Johnson', 'IT', '2020-11-10', 75000.00),
(4, 'Emily', 'Davis', 'HR', '2017-09-02', 54000.00),
(5, 'David', 'Miller', 'Finance', '2021-01-25', 67000.00),
(6, 'Sarah', 'Wilson', 'Operations', '2016-04-19', 58000.00),
(7, 'James', 'Moore', 'Sales', '2018-02-12', 49000.00),
(8, 'Linda', 'Taylor', 'Marketing', '2022-06-14', 72000.00),
(9, 'Robert', 'Anderson', 'IT', '2015-08-05', 80000.00),
(10, 'Patricia', 'Thomas', 'HR', '2019-10-30', 52000.00);

SELECT * FROM Employees;

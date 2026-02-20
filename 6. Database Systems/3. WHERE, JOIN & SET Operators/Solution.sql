
-- Q1
SELECT * FROM employee
ORDER BY fname, lname;

-- Q2
SELECT fname from employee
WHERE salary >= 50000;

-- Q3
SELECT * FROM department
JOIN dept_locations 
ON department.dnumber = dept_locations.dnumber
WHERE dname = 'HR';

-- Q4
SELECT salary, dno FROM employee
WHERE sex = 'F';

-- Q5
SELECT fname from employee
WHERE salary >= 4000 AND salary <= 50000;

-- Q6
SELECT DISTINCT fname FROM employee
WHERE dno = 5;

-- Q7
UPDATE project
SET plocation = 'London'
WHERE pname = 'Kappa';

-- Q8
DELETE FROM project
WHERE pname = 'Iota';

-- Q9
SELECT fname, lname FROM employee
EXCEPT 
SELECT fname, lname FROM employee
WHERE dno = 7;

-- Q10
UPDATE employee
SET salary = 51000
WHERE lname = 'Wilson';

-- Q11
UPDATE employee
SET salary = salary * 1.10
WHERE dno = 4;

-- Q12
SELECT dlocation FROM dept_locations
UNION
SELECT plocation FROM project;

-- Q13
SELECT dlocation FROM dept_locations
EXCEPT
SELECT plocation FROM project;

-- Q14
SELECT dlocation FROM dept_locations
INTERSECT
SELECT plocation FROM project;

-- Q15
SELECT fname, lname FROM employee
WHERE dno = 
(SELECT dnumber FROM department
WHERE dname = 'HR');

-- Q16
SELECT dname, COUNT(*) AS Count
FROM department
JOIN project 
ON department.dnumber = project.dnum
WHERE project.plocation = 'New York'
GROUP BY dname;

-- Q17
SELECT fname, lname, salary
FROM employee
WHERE ssn IN
(SELECT essn FROM works_on
WHERE hours >= 30);

-- Q18
SELECT dnumber, dlocation AS 'Female Department Locations'
FROM dept_locations
WHERE dnumber NOT IN
(SELECT dno
FROM employee
WHERE sex = 'M');

-- Q19
SELECT DISTINCT employee.fname AS 'Employee First Name',
dependent.dependent_name AS 'Dependent Name'
FROM employee
JOIN dependent ON employee.ssn = dependent.essn;

-- Q20
SELECT employee.fname AS 'Employee First Name',
dependent.dependent_name AS 'Dependent Name'
FROM employee
JOIN dependent ON employee.ssn = dependent.essn
WHERE employee.fname = dependent_name;

-- Q21
SELECT * FROM department
WHERE dnumber IN
(SELECT dnumber FROM dept_locations
WHERE dlocation LIKE 'S%');

-- Q21
SELECT * FROM department
WHERE dnumber IN
(SELECT dnumber FROM dept_locations
WHERE dlocation LIKE 'S%');

-- Q22
SELECT * FROM project
WHERE plocation LIKE '%s%'
AND lower(plocation) NOT LIKE 's%'
AND lower(plocation) NOT LIKE '%s';

-- Practice Question
SELECT employee.* FROM employee
JOIN dependent
ON employee.ssn = dependent.essn
WHERE employee.dno IN
(SELECT dnumber FROM department
WHERE dname = 'Finance'
OR dname = 'Marketing')
EXCEPT
SELECT employee.* FROM employee
JOIN dependent
ON employee.ssn = dependent.essn
WHERE employee.ssn IN
(SELECT essn FROM works_on
WHERE hours >= 20
AND hours <= 30);
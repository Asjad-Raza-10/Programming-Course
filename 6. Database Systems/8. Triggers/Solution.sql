-- Q1
CREATE TRIGGER trg_after_insert_player
ON player
AFTER INSERT
AS
BEGIN
    PRINT 'A new player has been added.';
END;

-- Q2
CREATE TRIGGER trg_after_delete_team
ON team
AFTER DELETE
AS
BEGIN
    DECLARE @name VARCHAR(25);
    SELECT @name = tname FROM deleted;
    PRINT 'Deleted team: ' + @name;
END;

-- Q3
CREATE TRIGGER trg_after_update_salary
ON player
AFTER UPDATE
AS
BEGIN
    DECLARE @old DECIMAL(10,2), @new DECIMAL(10,2);
    SELECT @old = salary FROM deleted;
    SELECT @new = salary FROM inserted;

    IF ABS(@new - @old) > 5000
        PRINT 'Salary changed by more than 5000.';
END;

-- Q4
CREATE TRIGGER trg_insteadof_insert_player
ON player
INSTEAD OF INSERT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM inserted WHERE age < 18)
        PRINT 'Insert blocked: player age is less than 18.';
    ELSE
        INSERT INTO player SELECT * FROM inserted;
END;

-- Q5
ALTER TABLE player ADD total_runs INT DEFAULT 0;
ALTER TABLE player ADD total_wickets INT DEFAULT 0;

CREATE TRIGGER trg_after_insert_performance
ON performance
AFTER INSERT
AS
BEGIN
    UPDATE player
    SET total_runs = total_runs + i.runs,
        total_wickets = total_wickets + i.wickets
    FROM player p
    JOIN inserted i ON p.pid = i.pid;
END;

-- Q6
-- using INSTEAD OF because of the FK constraint
CREATE TRIGGER trg_insteadof_delete_team_players
ON team
INSTEAD OF DELETE
AS
BEGIN
    -- First delete players of this team
    DELETE FROM player
    WHERE tid IN (SELECT tid FROM deleted);

    -- Then delete the team itself
    DELETE FROM team
    WHERE tid IN (SELECT tid FROM deleted);
END;

-- Q7
CREATE TRIGGER trg_after_update_match_winner
ON match
AFTER UPDATE
AS
BEGIN
    IF EXISTS (
        SELECT 1 FROM inserted i
        JOIN deleted d ON i.mid = d.mid
        WHERE i.winner_id <> d.winner_id
    )
        PRINT 'Match winner has been changed.';
END;

-- Q8
CREATE TRIGGER trg_insteadof_delete_player
ON player
INSTEAD OF DELETE
AS
BEGIN
    IF EXISTS (
        SELECT 1 FROM performance
        WHERE pid IN (SELECT pid FROM deleted)
    )
        PRINT 'Delete blocked: player has performance records.';
    ELSE
        DELETE FROM player WHERE pid IN (SELECT pid FROM deleted);
END;

-- Q9
CREATE TRIGGER trg_after_insert_perf_multirow
ON performance
AFTER INSERT
AS
BEGIN
    DECLARE @total INT;
    SELECT @total = SUM(runs) FROM inserted;
    PRINT 'Total runs added in this operation: ' + CAST(@total AS VARCHAR);
END;

-- Q10
CREATE TABLE audit_salary (
    audit_id    INT IDENTITY PRIMARY KEY,
    pid         INT,
    old_salary  DECIMAL(10,2),
    new_salary  DECIMAL(10,2),
    changed_at  DATETIME DEFAULT GETDATE()
);

CREATE TRIGGER trg_audit_salary
ON player
AFTER UPDATE
AS
BEGIN
    INSERT INTO audit_salary (pid, old_salary, new_salary)
    SELECT i.pid, d.salary, i.salary
    FROM inserted i
    JOIN deleted d ON i.pid = d.pid
    WHERE i.salary <> d.salary;
END;

-- Testing the triggers now

-- Q1
INSERT INTO player VALUES ('Test Player', 201, 22, 'Batsman', 50000, 1, NULL, NULL, NULL);

-- Q2
INSERT INTO team VALUES ('Test Team', 99, 'Test Coach', 'Test City');
DELETE FROM team WHERE tid = 99;

-- Q3
-- Should trigger message (change is 10000)
UPDATE player SET salary = 100000 WHERE pid = 101;

-- Should NOT trigger message (change is only 1000)
UPDATE player SET salary = 101000 WHERE pid = 101;

-- Q4
-- Should be BLOCKED
INSERT INTO player VALUES ('Kid Player', 202, 15, 'Batsman', 30000, 1, NULL, NULL, NULL);

-- Should be ALLOWED
INSERT INTO player VALUES ('Adult Player', 203, 20, 'Batsman', 30000, 1, NULL, NULL, NULL);

-- Q5
UPDATE player SET total_runs = 0, total_wickets = 0;
-- Check values before
SELECT pid, total_runs, total_wickets FROM player WHERE pid = 101;

-- Insert performance row
INSERT INTO performance VALUES (101, 203, 40, 1, 0);

-- Check values after — should increase by 40 runs, 1 wicket
SELECT pid, total_runs, total_wickets FROM player WHERE pid = 101;

-- Q6
INSERT INTO team VALUES ('Temp Team', 88, 'Temp Coach', 'Temp City');
INSERT INTO player VALUES ('Temp Player', 299, 25, 'Bowler', 40000, 88, NULL, NULL, NULL);

SELECT * FROM player WHERE tid = 88;  -- should show Temp Player

DELETE FROM team WHERE tid = 88

SELECT * FROM player WHERE tid = 88;  -- should return no rows

-- Q7
-- Should print message (as winner changes from 1 to 2)
UPDATE match SET winner_id = 2 WHERE mid = 201;

-- Should NOT print message (as winner stays the same)
UPDATE match SET venue = 'Multan' WHERE mid = 201;

-- Q8
-- Should be BLOCKED (pid 101 has performance records)
DELETE FROM player WHERE pid = 101;

-- Insert a player with no performance records, then delete — should be ALLOWED
INSERT INTO player VALUES ('No Stats Player', 301, 24, 'Bowler', 45000, 1, NULL, NULL, NULL);
DELETE FROM player WHERE pid = 301;

-- Q9
-- Single row insert — should print total runs = 30
INSERT INTO performance VALUES (106, 204, 30, 1, 0);

-- Multi-row insert — should print total runs = 90 (25+65)
INSERT INTO performance VALUES 
(107, 205, 25, 0, 1),
(108, 202, 65, 0, 0);

-- Q10
-- Update salary
UPDATE player SET salary = 95000 WHERE pid = 102;

-- Check audit table — should have 1 row with old/new salary and pid
SELECT * FROM audit_salary;

-- Update two players at once
UPDATE player SET salary = salary + 5000 WHERE tid = 1;

-- Audit table should now have more rows
SELECT * FROM audit_salary ORDER BY changed_at DESC;
-- Q1
BEGIN TRANSACTION;
INSERT INTO team VALUES ('Quetta Gladiators', 5, 'Viv Richards', 'Quetta');
COMMIT;
PRINT 'Committed.';

-- Q2
BEGIN TRANSACTION;
INSERT INTO player VALUES ('New Player', 109, 25, 'Batsman', 60000, 1, NULL);
ROLLBACK;
PRINT 'Rolled back.';

-- Q3
BEGIN TRANSACTION;
INSERT INTO team VALUES ('Multan Sultans', 6, 'Andy Flower', 'Multan');
INSERT INTO player VALUES ('Mohammad Rizwan', 110, 30, 'Wicketkeeper', 85000, 6, NULL);
INSERT INTO player VALUES ('Shan Masood', 111, 28, 'Batsman', 70000, 6, 110);
COMMIT;
PRINT 'Committed.';

-- Q4
BEGIN TRANSACTION;
UPDATE player
SET salary = salary + 15000
WHERE pid = 101;
IF (SELECT salary FROM player WHERE pid = 101) > 100000
BEGIN
    ROLLBACK;
    PRINT 'Rolled back: salary exceeds 100000.';
END
ELSE
BEGIN
    COMMIT;
    PRINT 'Committed.';
END

-- Q5
BEGIN TRANSACTION;
-- deleted from performance before because of fk constraint
DELETE FROM performance WHERE mid = 205;
DELETE FROM match WHERE mid = 205;
IF @@ROWCOUNT = 0
BEGIN
    ROLLBACK;
    PRINT 'Rolled back: no match found.';
END
ELSE
BEGIN
    COMMIT;
    PRINT 'Committed.';
END

-- Q6
BEGIN TRANSACTION;
INSERT INTO team VALUES ('Rawalpindi Rams', 7, 'Inzamam-ul-Haq', 'Rawalpindi');
SAVE TRANSACTION sp1;
INSERT INTO player VALUES ('Abid Ali', 112, 32, 'Batsman', 65000, 7, NULL);
INSERT INTO player VALUES ('Yasir Shah', 113, 35, 'Bowler', 68000, 7, 112);
ROLLBACK TRANSACTION sp1;
PRINT 'Rolled back to savepoint: player inserts undone.';
COMMIT;
PRINT 'Committed: team insert saved.';

-- Q7
BEGIN TRANSACTION;
UPDATE player SET tid = 3 WHERE pid = 101;
INSERT INTO performance VALUES (101, 202, 80, 0, 1);
IF NOT EXISTS (
    SELECT 1 FROM match
    WHERE mid = 202
      AND (team1_id = 3 OR team2_id = 3)
)
    BEGIN
        ROLLBACK;
        PRINT 'Rolled back: player not in this match.';
    END
ELSE
    BEGIN
        COMMIT;
        PRINT 'Committed.';
    END
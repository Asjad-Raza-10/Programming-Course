-- Q1
CREATE TRIGGER trg_player_captain_team
ON player
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT 1 FROM inserted i
        JOIN player p ON i.captain_id = p.pid
        WHERE i.captain_id IS NOT NULL
          AND i.tid != p.tid
    )
    BEGIN
        RAISERROR('Captain must belong to the same team.', 16, 1);
        ROLLBACK;
    END
END;

-- captain_id 101 belongs to team 1, but new player is in team 2 → trigger fires
INSERT INTO player VALUES ('Test Player', 206, 25, 'Batsman', 60000, 2, 101,25,2);

-- Q2
CREATE TRIGGER trg_player_tid_update
ON player
AFTER UPDATE
AS
BEGIN
    IF EXISTS (
        SELECT 1 FROM inserted i
        JOIN deleted d ON i.pid = d.pid
        JOIN player p ON p.captain_id = i.pid
        WHERE i.tid != d.tid
    )
    BEGIN
        RAISERROR('Cannot change team: player is assigned as captain of other players.', 16, 1);
        ROLLBACK;
    END
END;

-- pid 101 is captain of pid 102, moving him to team 2 → trigger fires
UPDATE player SET tid = 2 WHERE pid = 101;

-- Q3
CREATE TRIGGER trg_player_delete_reassign
ON player
INSTEAD OF DELETE
AS
BEGIN
    UPDATE player
    SET captain_id = NULL
    WHERE captain_id IN (SELECT pid FROM deleted);

    DELETE FROM player
    WHERE pid IN (SELECT pid FROM deleted);
END;

-- FK Constraint was not letting us delet from player, becase pid 101 is also in the performance table.
ALTER TABLE performance
DROP CONSTRAINT FK__performance__pid__5AEE82B9;
DELETE FROM player WHERE pid = 101;
SELECT pid, pname, captain_id FROM player WHERE pid = 102;

-- pid 101 is captain of pid 102, deleting 101 → 102's captain_id becomes NULL first, then 101 is deleted
DELETE FROM player WHERE pid = 101;
SELECT pid, pname, captain_id FROM player WHERE pid = 102;

-- Q4
CREATE TRIGGER trg_match_same_team
ON match
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT 1 FROM inserted
        WHERE team1_id = team2_id
    )
    BEGIN
        RAISERROR('A team cannot play against itself.', 16, 1);
        ROLLBACK;
    END
END;

-- team1_id = team2_id = 1 → trigger fires
INSERT INTO match VALUES (301, '2025-01-01', 'Lahore', 1, 1, NULL, 1);

-- Q5
CREATE TRIGGER trg_match_winner_valid
ON match
AFTER UPDATE
AS
BEGIN
    IF EXISTS (
        SELECT 1 FROM inserted
        WHERE winner_id IS NOT NULL
          AND winner_id != team1_id
          AND winner_id != team2_id
    )
    BEGIN
        RAISERROR('Winner must be one of the two teams in the match.', 16, 1);
        ROLLBACK;
    END
END;

-- match 201 is between team 1 and 2, setting winner to team 3 → trigger fires
UPDATE match SET winner_id = 3 WHERE mid = 201;

-- Q6
CREATE TRIGGER trg_performance_team_check
ON performance
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT 1 FROM inserted i
        JOIN player p ON i.pid = p.pid
        JOIN match  m ON i.mid = m.mid
        WHERE p.tid != m.team1_id
          AND p.tid != m.team2_id
    )
    BEGIN
        RAISERROR('Player team did not participate in this match.', 16, 1);
        ROLLBACK;
    END
END;

-- pid 107 belongs to team 4, match 201 is between team 1 and 2 → trigger fires
INSERT INTO performance VALUES (107, 201, 30, 1, 0);

-- Q7
CREATE TRIGGER trg_performance_not_both_zero
ON performance
AFTER UPDATE
AS
BEGIN
    IF EXISTS (
        SELECT 1 FROM inserted
        WHERE runs = 0 AND wickets = 0
    )
    BEGIN
        RAISERROR('Runs and wickets cannot both be zero.', 16, 1);
        ROLLBACK;
    END
END;

-- pid 101, mid 201 currently has runs=75, setting both to 0 → trigger fires
UPDATE performance SET runs = 0, wickets = 0 WHERE pid = 101 AND mid = 201;

-- Q8
CREATE TRIGGER trg_tournament_delete_check
ON tournament
AFTER DELETE
AS
BEGIN
    IF EXISTS (
        SELECT 1 FROM match m
        JOIN deleted d ON m.tour_id = d.tour_id
    )
    BEGIN
        RAISERROR('Cannot delete tournament: matches exist for it.', 16, 1);
        ROLLBACK;
    END
END;

-- tour_id 1 has matches 201, 202, 203 linked to it → trigger fires
DELETE FROM tournament WHERE tour_id = 1;

-- Q9
CREATE TRIGGER trg_match_min_players
ON match
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT 1 FROM inserted i
        WHERE (SELECT COUNT(*) FROM player WHERE tid = i.team1_id) < 11
           OR (SELECT COUNT(*) FROM player WHERE tid = i.team2_id) < 11
    )
    BEGIN
        RAISERROR('Both teams must have at least 11 players.', 16, 1);
        ROLLBACK;
    END
END;

-- team 1 has only 2 players, team 2 has only 2, both < 11 → trigger fires
INSERT INTO match VALUES (302, '2025-05-01', 'Karachi', 1, 2, NULL, 2);

-- Q10
CREATE TRIGGER trg_player_salary_cap
ON player
AFTER UPDATE
AS
BEGIN
    IF EXISTS (
        SELECT 1 FROM inserted i
        WHERE i.salary > 2 * (
            SELECT AVG(salary) FROM player WHERE tid = i.tid
        )
    )
    BEGIN
        RAISERROR('Salary exceeds twice the team average salary.', 16, 1);
        ROLLBACK;
    END
END;

-- team 1 avg salary = 87500, twice = 175000, setting 999999 → trigger fires
UPDATE player SET salary = 999999 WHERE pid = 101;
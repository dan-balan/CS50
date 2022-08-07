-- Keep a log of any SQL queries you execute as you solve the mystery.

-- INPUT
-- details about crime scene
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = "Chamberlin Street";

-- OUTPUT
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time
-- each of their interview transcripts mentions the courthouse.

-- INPUT
-- witnesses interview
SELECT name, transcript FROM interviews
WHERE year = 2020 AND day = 28 AND month = 7
AND transcript LIKE "%courthouse%";

/* OUTPUT
Ruth |
Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
Eugene |
I don't know the thief's name, but it was someone I recognized.
Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
Raymond |
As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/

-- INPUT
-- courthouse_security_logs

SELECT * FROM courthouse_security_logs
WHERE year = 2020 AND month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 15 and 25
AND activity = "exit"
;

-- INPUT
-- Eugene clues: ATM

SELECT * FROM atm_transactions
WHERE year = 2020 AND month = 7
AND day = 28
AND atm_location LIKE "%Fifer%"
AND transaction_type = "withdraw"
;

-- Ruth clues: name of suspets that where withdrawing money from Fifer Street
SELECT name, FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE people.id IN
(
SELECT person_id FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE bank_accounts.account_number IN
(
SELECT account_number FROM atm_transactions
WHERE year = 2020 AND month = 7
AND day = 28
AND atm_location LIKE "%Fifer%"
AND transaction_type = "withdraw"
)
);


-- INPUT
-- Raymond clues: phone call

SELECT * FROM phone_calls
WHERE year = 2020 AND month = 7
AND day = 28
AND duration < 60
;

-- INPUT
-- Ruth clues + Eugene clues => suspects list

SELECT DISTINCT(people.id), name, license_plate FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_number IN
(
SELECT phone_calls.caller FROM phone_calls
WHERE year = 2020 AND month = 7
AND day = 28
AND duration < 60
)
AND license_plate IN
(SELECT license_plate FROM courthouse_security_logs
WHERE year = 2020 AND month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 10 and 30
AND activity = "exit")
;

-- OUTPUT
-- suspects list =>Roger, Russell, Evelyn, Ernest


-- Ruth clues + Eugene clues + Raymond clues => short suspects list: Russell, Ernest
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE people.id IN
    (
    SELECT person_id FROM bank_accounts
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE bank_accounts.account_number IN
        (
        -- Eugene clues: ATM
        SELECT account_number FROM atm_transactions
        WHERE year = 2020 AND month = 7
        AND day = 28
        AND atm_location LIKE "%Fifer%"
        AND transaction_type = "withdraw"
        )
    )
AND people.name IN
    (
    -- Ruth clues + Eugene clues => suspects list
    SELECT name FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
    WHERE phone_number IN
        (
        -- Raymond clues: phone call
        SELECT phone_calls.caller FROM phone_calls
        WHERE year = 2020 AND month = 7
        AND day = 28
        AND duration < 60
        )
    AND license_plate IN
        (
        -- Ruth clues: courthouse_security_logs
        SELECT license_plate FROM courthouse_security_logs
        WHERE year = 2020 AND month = 7
        AND day = 28
        AND hour = 10
        AND minute BETWEEN 10 and 30
        AND activity = "exit")
    )
;


-- calls done by the suspects Ernest and Russell
-- calls to ...
SELECT DISTINCT(people.id), name, passport_number FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE people.phone_number IN
(
    SELECT phone_calls.receiver FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
    WHERE phone_calls.id IN
    (
    SELECT phone_calls.id FROM phone_calls
    WHERE year = 2020 AND month = 7
    AND day = 28
    AND duration < 60
    )
    AND people.name = 'Ernest' OR people.name = 'Russell'
    AND phone_calls.duration < 60
)
;


-- morning flights of the suspects => only Ernest have a flight at the first hour on 29th
SELECT people.name, passengers.*, flights.*, airports.*, destination_airport_id FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE passengers.passport_number IN

(SELECT passport_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE people.id IN
    (
    SELECT person_id FROM bank_accounts
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE bank_accounts.account_number IN
        (
        -- Eugene clues: ATM
        SELECT account_number FROM atm_transactions
        WHERE year = 2020 AND month = 7
        AND day = 28
        AND atm_location LIKE "%Fifer%"
        AND transaction_type = "withdraw"
        )
    )
AND people.name IN
    (
    -- Ruth clues + Eugene clues => suspects list
    SELECT name FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
    WHERE phone_number IN
        (
        -- Raymond clues: phone call
        SELECT phone_calls.caller FROM phone_calls
        WHERE year = 2020 AND month = 7
        AND day = 28
        AND duration < 60
        )
    AND license_plate IN
        (
        -- Ruth clues: courthouse_security_logs
        SELECT license_plate FROM courthouse_security_logs
        WHERE year = 2020 AND month = 7
        AND day = 28
        AND hour = 10
        AND minute BETWEEN 10 and 30
        AND activity = "exit")
    )
)
AND flights.hour < 12
AND flights.day = 29
;
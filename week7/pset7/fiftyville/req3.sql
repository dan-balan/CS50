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
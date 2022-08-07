-- banc account
SELECT passengers.*, flights.*, airports.* FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE passengers.passport_number IN
(
SELECT DISTINCT(people.passport_number) FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions  ON bank_accounts.account_number = atm_transactions.account_number
WHERE people.name = "Berthold" OR people.name = "Philip"
);
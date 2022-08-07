SELECT phone_calls.duration, name, passport_number, phone_calls.* FROM people
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
    AND people.name = 'Ernest' 
    AND phone_calls.duration < 60
)
AND phone_calls.duration < 60
;

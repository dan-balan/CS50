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



/*
SELECT phone_calls.id, caller, receiver, people.name FROM phone_calls
inner JOIN people
ON --phone_calls.caller = people.phone_number AND
    phone_calls.receiver = people.phone_number
WHERE phone_calls.id IN
    (
    SELECT phone_calls.id FROM phone_calls
    --SELECT phone_calls.* FROM phone_calls
    WHERE year = 2020 AND month = 7
    AND day = 28
    AND duration < 60
    )
--AND people.name = 'Ernest' OR people.name = 'Russell'
AND phone_calls.duration < 60
;

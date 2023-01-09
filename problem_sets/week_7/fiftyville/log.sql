SELECT * FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2021 AND street = 'Humphrey Street'; -- get the crime scene report
-- 10:15 AM at the bakery.  three witnesses were interviewed, their interviews mention the word bakery

SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';
-- 161|Ruth|2021|7|28|Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 162|Eugene|2021|7|28|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- 163|Raymond|2021|7|28|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

--  the thief is:
SELECT * FROM people 
WHERE phone_number 
IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) 
AND license_plate 
IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute < 26 AND activity = 'exit') 
AND id 
IN (SELECT id FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'))) 
AND passport_number
IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour, minute LIMIT 1));

--  the accomplice is:
SELECT * FROM people 
WHERE phone_number = (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE name = 'Bruce'));

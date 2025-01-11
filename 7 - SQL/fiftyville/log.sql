-- Keep a log of any SQL queries you execute as you solve the mystery.

-- CLUES:

    -- Theft : 28 / 07 / 2023

    -- Theft of the CS50 duck took place at 10:15am at the Humphrey Street BAKERY.

    -- Three witnesses who were present at the time.

    -- Littering took place at 16:36. No known witnesses.

    -- WITNESS INTERVIEWS:
        -- Ten minutes of the theft, the thief get into a car in the bakery parking lot and drive away (Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.)

        -- The thief there withdrawing some money on Leggett Street (I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.)

        -- The thief and someone were planning by call to take the earliest flight out of Fiftyville tomorrow (07/29/2023) - 29 July 2023 (As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.)

    -- SUSPECTS THIEF:
        -- Name       |     Number     |     Passport    |    License    |  Was in Bank? |   Call on 28th? |  Was in the plane?
        -- Vanessa [X]| (725) 555-4692 | 2963008352      | 5P2BI95       |      NOT      |       NOT       |        NOT
        -- Barry   [X]| (301) 555-4174 | 7526138472      | 6P58WS2       |      NOT      |       NOT       |        NOT
        -- Iman    [X]| (829) 555-5269 | 7049073643      | L93JTIZ       |      YES      |       NOT       |        NOT
        -- Sofia   [X]| (130) 555-0289 | 1695452385      | G412CB7       |      NOT      |       NOT       |        NOT
        -- Luca    [X]| (389) 555-5198 | 8496433585      | 4328GD8       |      YES      |       NOT       |        NOT
        -- Diana   [X]| (770) 555-1861 | 3592750733      | 322W7JE       |      YES      |       YES       |        NOT
        -- Kelsey  [X]| (499) 555-9472 | 8294398571      | 0NTHK55       |      NOT      |       NOT       |        NOT
        -- Bruce      | (367) 555-5533 | 5773159633      | 94KL13X       |      YES      |       YES       |        YES

    -- SUSPECTS ACCOMPLICE:
        -- Name   |     Number     |  Passport  | License
        -- Robin  | (375) 555-8161 | NULL       | 4V16VO0
        -- Philip | (725) 555-3243 | 3391710505 | GW362R6

    -- AIRPORTS:
        -- First flight of 29th July was going to New York City

    -- ATM:
        -- Bruce, Kaelyn, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista

------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- I will start seeing the tables that are in db
  .schema

-- I wanna find the crime scene to start the investigation
  SELECT * FROM crime_scene_reports
  WHERE day = 28 AND month = 7 AND year = 2023
  AND street = 'Humphrey Street';

-- I wanna see the transcripts from the witnesses interviews
  SELECT * FROM interviews
  WHERE year = 2023 AND month = 7
  AND day = 28;

-- I wanna see the cars that was going out within 10 minutes the thief
  SELECT * FROM bakery_security_logs
  WHERE year = 2023 AND month = 7 AND day = 28
  AND hour = 10;

-- I wanna see the city of the flights from the 29th July 2023
  SELECT * FROM airports
  JOIN flights ON airports.id = flights.destination_airport_id
  WHERE day = 29 AND month = 7 AND year = 2023
  ORDER BY flights.hour;

-- I wanna see the phone calls that happened in the same time of the theft
  SELECT * FROM phone_calls
  WHERE day = 28 AND month = 7 AND year = 2023
  AND duration < 60;

-- I wanna see the names that were in the flight from New York:
  SELECT people.name, people.passport_number FROM people
  WHERE people.passport_number IN(
    SELECT passengers.passport_number FROM passengers
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON airports.id = flights.destination_airport_id
    WHERE flights.day = 29 AND flights.month = 7 AND flights.year = 2023
    AND airports.city = 'New York City'
  );

-- I wanna see the transactions and the name of people that used the bank on 28th July
  SELECT * FROM people
  JOIN bank_accounts ON bank_accounts.person_id = people.id
  WHERE bank_accounts.account_number IN(
    SELECT atm_transactions.account_number FROM atm_transactions
    WHERE day = 28 AND month = 7 AND year = 2023
    AND atm_location = 'Leggett Street'
  );

-- I wanna see the name of the people that were in the bakery within 10 minutes of the theft
  SELECT * FROM people
  WHERE people.license_plate IN(
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2023 AND month = 7 AND day = 28
    AND hour = 10 AND minute > 15 AND minute < 25
  );

-- I wanna see better the phone calls that happened on 28th July
  SELECT * FROM people
  WHERE people.phone_number IN(
    SELECT phone_calls.caller FROM phone_calls
    WHERE day = 28 AND month = 7 AND year = 2023
    AND duration < 60
  );

  SELECT * FROM people
  WHERE people.phone_number IN(
    SELECT phone_calls.receiver FROM phone_calls
    WHERE day = 28 AND month = 7 AND year = 2023
    AND duration < 60
  );

SELECT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies On movies.id = stars.movie_id
WHERE movies.year = 2004
GROUP BY people.name
ORDER BY people.birth;

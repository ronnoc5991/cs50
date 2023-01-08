SELECT AVG(ratings.rating), movies.title 
FROM ratings 
INNER JOIN movies ON movies.id = ratings.movie_id 
WHERE movie_id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Chadwick Boseman')) GROUP BY movie_id ORDER BY rating DESC LIMIT 5;

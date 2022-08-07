-- a SQL query to list all movies released in 2010 and their ratings

SELECT title, rating FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE year = 2010 AND rating IS NOT NULL
ORDER BY rating DESC, title ASC;


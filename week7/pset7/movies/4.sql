-- a SQL query to determine the number of movies with an IMDb rating of 10.0

SELECT COUNT(title) FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE rating = 10.0;
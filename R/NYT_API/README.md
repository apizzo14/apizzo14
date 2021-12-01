## New York Times Movie Review API

In this project, I utilized the NYT Movie Review API. I coded the function movie_info that is passed a certain query, start date, end date, and key. This function returns a dataframe containing relevant movies that contain contain the query keyword, as well as the opening date, summary and review url of that movie.
Other functions return the review by searching the url in google chrome by a system call in bash, and say the summary using another system call.
Using my functions, I determined how many movies were reviewed by NYT. I found the movie with the longest summary and used a system call to read the summary and to open the review in a google chrome page.

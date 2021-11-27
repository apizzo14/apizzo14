#a class that will act as a database for a movie store
#attributes: movieTitle, movieGenre, MovieRating, addCart
#methods: addMovie, getTitle, getGenre, getRating
#the user will search through a catalogue and select movies they would like to add to their cart,
#the database alse supplies information on the movie's genre and rating
class Movie:
    def __init__(self, title):
        self.movieTitle= title
        self.movieGenre= ""
        self.movieRating= ""
        self.addCart=0

    def addMovie(self, title): #adds a movie to the catalogue of movies
        self.movieTitle=title #adds movie title to class attribute
        genre=input("What is the genre of "+title+"?\n") #asks for user input to then add movie genre to class attribute
        rating=input("What is the rating of "+title+"?\n") #asks for user input to then add movie rating to class attribute
        self.movieGenre=genre
        self.movieRating=rating
        print("Ok, "+title+" has been added to the catalogue.")

    def getTitle(self): #returns the title of a certain movie
        return self.movieTitle

    def getGenre(self, title): #returns the rating of a certain movie
        try: #for movies already existing in the catalogue
            MovieTitleDatabase=["Parasite", "1917", "Knives Out", "Little Women", "Joker", "Avengers Endgame", "Jumanji The Next Level", "Once Upon a Time in Hollywood", "Jojo Rabbit", "Star Wars The Rise of Skywalker"]
            MovieGenreDatabase=["Thriller", "War/Drama", "Mystery", "Romance/Drama", "Drama/Crime", "Action", "Comedy/Action", "Comedy/Drama", "Comedy", "Sci-fi/Adventure"]
            index=MovieTitleDatabase.index(title)
            return MovieGenreDatabase[index]
        except: #for movies that have been added to the catalogue
            return self.movieGenre

    def getRating(self, title): #returns the rating of a certain movie
        try: #for movies already existing in the catalogue
            MovieTitleDatabase=["Parasite", "1917", "Knives Out", "Little Women", "Joker", "Avengers Endgame", "Jumanji The Next Level", "Once Upon a Time in Hollywood", "Jojo Rabbit", "Star Wars The Rise of Skywalker"]
            MovieRatingDatabase=["R", "R", "PG-13", "PG", "R", "PG-13", "PG-13", "R", "PG-13", "PG-13"]
            index=MovieTitleDatabase.index(title)
            return MovieRatingDatabase[index]
        except: #for movies that have been added to the catalogue
            return self.movieRating


import time #import so that pauses can be inserted, allowing user to read information in chunks

def main():
    print("Welcome to the Online Movie Store!\n") #welcome statement
    time.sleep(1)
    print("Here is our catalogue of movies:") #displays movies in preexisting catalogue
    time.sleep(1)
    MovieTitleDatabase=["Parasite", "1917", "Knives Out", "Little Women", "Joker", "Avengers Endgame", "Jumanji The Next Level", "Once Upon a Time in Hollywood", "Jojo Rabbit", "Star Wars The Rise of Skywalker"]
    print(MovieTitleDatabase)
    time.sleep(1)
    addMovie=input("Would you like to add a movie to the catalogue?\n") #user is able to add a movie to the movie catalogue
    while addMovie.capitalize()=="Yes": #loop allowing user to add as many movies to the catalogue as they want
        newMovie=input("Ok, what is the title of the new movie?\n")
        Movie(newMovie).addMovie(newMovie) #uses class method to add new movie with its attributes
        MovieTitleDatabase.append(newMovie) #adds movie to the display list
        addMovie=input("Would you like to add another movie to the catalogue?\n") #user is prompted again, if they enter "no" the loop will be broken
    print("Again, here is the catalogue") #displays catalogue with added movies
    time.sleep(1)
    print(MovieTitleDatabase)
    time.sleep(1)
    numMovies=int(input("How many movies would you like to research?\n"))
    cart=[] #user has a cart that they can add movies to
    for i in range(numMovies): #loop that will allow user to research as many movies as they entered
        print("Movie", i+1,":")
        movieTitle=input("Which movie would you like to look up?\n")
        while movieTitle not in MovieTitleDatabase: #loop will ensure that what the user enters is in the catalogue
            movieTitle=input("Which movie would you like to look up? Please make sure you spell correctly.\n")
            time.sleep(1)
        genre=Movie(movieTitle).getGenre(movieTitle) #acquires genre of movie from class attribute
        rating=Movie(movieTitle).getRating(movieTitle) #acquires rating of movie from class attribute
        print("The genre of", movieTitle, "is", genre)
        print("The rating of", movieTitle, "is", rating)
        time.sleep(1.5)
        addCart=input("Would you like to add this movie to your cart?\n") #user can add movies to their cart
        if addCart.capitalize()=="Yes":
            cart.append(movieTitle) #movie title will be added to cart
    print("Here is your cart:") #displays cart for user
    print(cart)
    time.sleep(1)
    editCart=input("Would you like to edit your cart?\n") #user can make corrections to their cart or edit if they changed their mind
    while editCart.capitalize()=="Yes":
        editIndex=int(input("What is the index of the movie you would like to edit?\n")) #user enters index of movie they would like to edit
        editAction=input("Would you like to remove or replace?\n")
        if editAction.capitalize()=="Remove": #movie is removed using function
            removeMovie(editIndex, cart) #removeMovie function is called
        if editAction.capitalize()=="Replace": #movie is replaced with another using function
            replaceMovie(editIndex, cart) #replaceMovie function is called
        print("Here is your new cart:") #prints updated cart
        print(cart)
        time.sleep(1)
        editCart=input("Would you like to edit your cart?\n") #user is promted again, if they enter "no" the loop will break
    print("Have a great day!")

def removeMovie(index, cart):
    cart.remove(cart[index]) #movie title is removed from the user's cart

def replaceMovie(index, cart):
    replacement=input("Which movie would you like to select instead?\n") #user enters the movie they would like to select instead
    MovieTitleDatabase=["Parasite", "1917", "Knives Out", "Little Women", "Joker", "Avengers Endgame", "Jumanji The Next Level", "Once Upon a Time in Hollywood", "Jojo Rabbit", "Star Wars The Rise of Skywalker"]
    while replacement not in MovieTitleDatabase: #loop ensure the new movie entered is in the catalogue
        replacement=input("Which movie would you like to select instead? Please make sure you spell correctly.\n") #user did not enter title correctly, they are prompted again
        time.sleep(1)
    cart.remove(cart[index]) #movie is removed at index entered by user
    cart.insert(index,replacement) #new movie is placed at that same index


main() #main function is called

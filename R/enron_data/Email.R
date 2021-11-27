test <- "../../datasets/maildir/."

Email <- function(filename)
{
  con <- file(filename, "r")
  ll <- readLines(con)
  close(con)
  return(ll)
}

to.Email <- function(em)
{
  from_ndx <- grep("X-To:", em)
  from_line <- em[from_ndx]
  split <- strsplit(from_line, ", ")
  first_name <- split[[1]][1]
  end <- nchar(first_name)
  first_name <- substr(first_name, 7, end)
  split[[1]][1] <- first_name
  return(split[[1]])
}

from.Email <- function(em)
{
  to_ndx <- grep("X-From:", em)
  to_line <- em[to_ndx]
  split <- strsplit(to_line, ": ")
  return(split[[1]][2])
}
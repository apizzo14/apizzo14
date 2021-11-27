test <- "allen-p"

Employee <- function(directory_name)
{
  sent_items_folder <- paste("../../datasets/maildir/", directory_name, "/sent_items/", sep = "")
  sent_folder <- paste("../../datasets/maildir/", directory_name, "/sent/", sep = "")
  if( dir.exists( sent_folder))
  {
    path <- sent_folder
  }
  else
  {
    path <- sent_items_folder
  }
  return(path)
}

get_number_of_emails.Employee <- function(e)
{
  num <- length(dir(e))
  return(num)
}

get_email_filename.Employee <- function(e, i)
{
  file <- dir(e)[i]
  return(file)
}

get_name.Employee <- function(e)
{
  file <- dir(e)[1]
  path <- paste(e, file, sep = "")
  email <- Email(path)
  name <- from.Email(email)
  return(name)
}
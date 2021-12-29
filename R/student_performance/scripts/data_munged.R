library(plyr)
library(dplyr)

#load csv file
get_data <- function()
{
  d <- read.csv("../data/StudentsPerformance.csv", header=T, stringsAsFactors=F)
  return(d)
}

#eliminate spaces from column names, edit some column names
clean_column_names <- function(d)
{
  names(d) <- c("gender", "race.ethnicity.group", "parental.education.level",
                "lunch.type", "test.preparation.course", "math.score", "reading.score",
                "writing.score")
  return(d)
}




library(plyr)
library(dplyr)

find_best_worst_factors <- function(d)
{
  df <- plyr::ddply(d, .(gender, race.ethnicity.group, parental.education.level, 
                         lunch.type, test.preparation.course), function(split_frame){
                           avg_math <- split_frame$math.score %>% sum / split_frame$math.score %>% length
                           avg_reading <- split_frame$reading.score %>% sum / split_frame$reading.score %>% length
                           avg_writing <- split_frame$writing.score %>% sum / split_frame$writing.score %>% length
                           avg_score <- (avg_math + avg_reading + avg_writing) / 3
    return(avg_score)
  })
  names(df) <- c("gender", "race.ethnicity.group", "parental.education.level",
    "lunch.type", "test.preparation.course", "avg.score")
  df <- dplyr::arrange(df, desc(avg.score))
  len <- df %>% nrow
  print("Factors with the highest average score: ")
  print(df[1,])
  print("Factors with the lowest average score: ")
  print(df[len,])
  return(df)
}

sort_by_parent_eduction <- function(d)
{
  df <- plyr::ddply(d, .(parental.education.level), function(split_frame){
                           avg_math <- split_frame$math.score %>% sum / split_frame$math.score %>% length
                           avg_reading <- split_frame$reading.score %>% sum / split_frame$reading.score %>% length
                           avg_writing <- split_frame$writing.score %>% sum / split_frame$writing.score %>% length
                           avg_score <- (avg_math + avg_reading + avg_writing) / 3
                           out_df <- data.frame(avg.math = avg_math, avg.reading = avg_reading, 
                                      avg.writing = avg_writing, overall.avg = avg_score,
                                      stringsAsFactors=F)
                           return(out_df)
                         })
  df <- dplyr::arrange(df, desc(overall.avg))
  print(df)
  return(df)
}

get_100s <- function(d)
{
  df <- dplyr::filter(d, math.score == 100 & reading.score == 100 & writing.score == 100)
  print(df)
  print("Number of people with all perfect scores: ")
  len <- df %>% nrow
  print(len)
}

most_aced_section <- function(d)
{
  aced_math <- dplyr::filter(d, math.score == 100)
  num_aced_math <- aced_math %>% nrow
  aced_reading <- dplyr::filter(d, reading.score == 100)
  num_aced_reading <- aced_reading %>% nrow
  aced_writing <- dplyr::filter(d, writing.score == 100)
  num_aced_writing <- aced_writing %>% nrow
  subject <- c("Math", "Reading", "Writing")
  num_100s <- c(num_aced_math, num_aced_reading, num_aced_writing)
  num_aces <- data.frame(subject, num_100s, stringsAsFactors = F)
  max_aces <- which.max(num_100s)
  print("Subject with the most 100s is: ")
  print(subject[max_aces])
  return(num_aces)
}
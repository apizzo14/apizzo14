library(wordcloud2)
library(dplyr)

get_word_counts <- function(d, speaker)
{
  speaker_lines_vec <- d[d$speaker == speaker,3]
  split <- strsplit(speaker_lines_vec, " ")
  split <- unlist(split)
  unique_words <- unique(split)
  num_times_said <- vector("numeric", length(unique_words))
  for (i in 1:length(unique_words))
  {
    num_times_said[i] <- length(grep(unique_words[i], split, fixed = T)) 
  }
  out_df <- data.frame(word = unique_words, count = num_times_said)
  return(out_df)
}

total_word_counts <- function(d, speakers)
{
  if (length(speakers) == 2)
  {
    d1 <- d[d$speaker == speakers[1] | d$speaker == speakers[2], ]
  }
  else if (length(speakers) == 3)
  {
    d1 <- d[d$speaker == speakers[1] | d$speaker == speakers[2]
                     | d$speaker == speakers[3], ]
  }
  split <- strsplit(d1$line, " ")
  split <- unlist(split)
  unique_words <- unique(split)
  num_times_said <- vector("numeric", length(unique_words))
  for (i in 1:length(unique_words))
  {
    num_times_said[i] <- length(grep(unique_words[i], split, fixed = T)) 
  }
  out_df <- data.frame(word = unique_words, count <- num_times_said)
  return(out_df)
}

prepare_word_cloud <- function(d, speaker)
{
  if (length(speaker)>1)
  {
    df <- total_word_counts(d, speaker)
  }
  else
  {
    df <- get_word_counts(d, speaker)
  }
  common_words_df <- read.csv("../data/word_frequency.csv", header=T, stringsAsFactors = F, strip.white = T)
  common_words <- toupper(common_words_df[1:500,2]) #vector is returned with spaces in front
  common_words <- clean_words(common_words)
  uncommon_words <- vector("character")
  freq <- vector("numeric")
  for (i in 1:length(df$word))
  {
    if (is.element(toupper(df$word[i]), common_words) == FALSE) #add the word to uncommon if it isn't in the common words df
    {
      uncommon_words <- c(uncommon_words, df$word[i])
      freq <- c(freq, df$count[df$word == df$word[i]])
    }
  }
  return(data.frame(uncommon_words, weight = freq))
}

clean_words <- function(words)
{
  for (i in 1:length(words))
  {
    split <- strsplit(words[i], "")
    split <- split[[1]][4:length(split[[1]])]
    the_word<-paste(split, collapse= "")
    words[i] <- the_word
  }
  return(words)
}


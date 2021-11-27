library("stringr")

munge_data <- function()
{
  con <- file("../data/Presidential_Debate_Transcript.txt", "r")
  lines <- readLines(con)
  lines <- setdiff(lines, "")
  close(con)
  ind <- grep("\\(", lines)
  time <- vector("character", length(ind))
  speaker <- vector("character", length(ind))
  their_line <- vector("character", length(ind))
  get_time_speaker <- lines[ind]
  speaker_header <- substr(get_time_speaker, 1, 3)
  for (i in 1:length(ind))
  {
    if (speaker_header[i] == "Chr") #Chris Wallace
    {
      speaker[i] <- "Wallace"
    }
    else if (speaker_header[i] == "Pre") #President Trump
    {
      speaker[i] <- "Trump"
    }
    else if (speaker_header[i] == "Vic") #VP Biden
    {
      speaker[i] <- "Biden"
    }
    time[i] <- get_time(get_time_speaker[i])
    for (i in 1:length(time))
    {
      time[i] <- str_replace(time[i], ":", "min")
      time[i] <- str_replace(time[i], "\\)", "sec")
    }
    their_line <- lines[ind+1]
    out_df <- data.frame(time, speaker, line = their_line)
  }
  return(out_df)
}
  
get_time <- function( line )
{
  split <- strsplit(line, split = "")
  start_ind <- grep("\\(", split[[1]])+1
  end_ind <- grep("\\)", split[[1]])
  time <- split[[1]][start_ind:end_ind]
  string_time <- paste(time, collapse= "")
  return(string_time)
}

d1 <- munge_data()

write.csv(d1, "debate.csv", row.names = F)


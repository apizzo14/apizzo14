library(plyr)
library(dplyr)

get_files <- function()
{
  yt_dir <- "../../../datasets/youtubeData/"
  read_files <- Map(function(file){
    path <- paste(yt_dir, file, sep="")
    fileCountry <- substr(file, 1, 2)
    theFile <- read.csv(path, header = T, stringsAsFactors = F)
    theFile$country = rep(fileCountry, length(theFile$video_id))
    return(theFile)
  }, dir(yt_dir))
  do.call(rbind, read_files)
}


make_df <- function()
{
  df <- get_files()
  get_info <- plyr::ddply(df, .(country), function(frame) {
    popTitle <- frame$title[which.max(frame$views)]
    dayViews <- Map(function(theDay){
      day_df <- dplyr::filter(frame, trending_date == theDay)
      totalViews <- day_df$views %>% sum
      day <- theDay
      out_df <- data.frame(day, totalViews, stringsAsFactors=F)
      return(out_df)
    }, frame$trending_date %>% unique)
    dayViews <- do.call(rbind, dayViews)
    busiestDay <- dayViews$day[which.max(dayViews$totalViews)]
    theCountry <- frame$country[1]
    nonCountry_df <- dplyr::filter(df, country != theCountry)
    unique_title <- setdiff(frame$title, nonCountry_df$title)
    unique_df <- dplyr::filter(frame, is.element(title, unique_title))
    uniquePopTitle <- unique_df$title[which.max(unique_df$views)]
    out_df <- data.frame(theCountry, popTitle, busiestDay, uniquePopTitle, stringsAsFactors=F)
    return(out_df)
  })
  return(get_info)
}


num_trends <- function()
{
  df <- get_files()
  get_info <- plyr::ddply(df, .(video_id), function(frame) {
    video_id <- frame$video_id[1]
    nCountry <- length(unique(frame$country))
    out_df <- data.frame(video_id, nCountry, stringsAsFactors=F)
    return(out_df)
  })
  return(get_info)
}


trend_all <- function()
{
  df <- get_files()
  df2 <- num_trends()
  all_countries <- list()
  for (i in 1:length(df2$nCountry))
  {
    if (df2$nCountry[i] == 10)
    {
      all_countries <- c(all_countries, df2$video_id[i])
    }
  }
  all_countries <- do.call(rbind, all_countries)
  all_countries <- as.vector(all_countries)
  all_countries <- setdiff(all_countries, "#NAME?")
  out_df <- dplyr::filter(df, is.element(video_id, all_countries))
  out_df <- dplyr::select(out_df, title)
  out_vec <- out_df$title %>% unique
}

library(lubridate)
library(ggplot2)

make_plot_1 <- function()
{
  df <- get_files()
  df <- dplyr::select(df, trending_date, views, country)
  
  days <- df$trending_date %>% unique
  countries <- df$country %>% unique
  plot_list <- list()
  for (i in 1:length(countries))
  {
    country_df <- dplyr::filter(df, country == countries[i])
    totalViews <- Map(function(date){
      day_df <- dplyr:: filter(country_df, trending_date == date)
      totalViews <- sum(day_df$views)
      return(totalViews)
    }, days)
    totalViews <- do.call(rbind, totalViews)
    plot_df <- data.frame(day = days, totalViews, country = rep(countries[i], length(totalViews)), stringsAsFactors = F)
    plot_list[[i]] <- plot_df
    names(plot_list)[i] <- countries[i]
  }
  plot_df <- do.call(rbind, plot_list)
  for (i in 1:length(plot_df$day))
  {
    plot_df$day[i] <- clean_date_num(plot_df$day[i])
  }
  g1 <- ggplot(data=plot_df) + geom_line(mapping=aes(x=day,
                                                     y=totalViews))
  return(g1)
}


make_plot_2 <- function()
{
  df <- get_files()
  df <- dplyr::select(df, trending_date, views, country)
  
  days <- df$trending_date %>% unique
  countries <- df$country %>% unique
  plot_list <- list()
  for (i in 1:length(countries))
  {
    country_df <- dplyr::filter(df, country == countries[i])
    totalViews <- Map(function(date){
      day_df <- dplyr:: filter(country_df, trending_date == date)
      totalViews <- sum(day_df$views)
      return(totalViews)
    }, days)
    totalViews <- do.call(rbind, totalViews)
    plot_df <- data.frame(day = days, totalViews, country = rep(countries[i], length(totalViews)), stringsAsFactors = F)
    plot_list[[i]] <- plot_df
    names(plot_list)[i] <- countries[i]
  }
  plot_df <- do.call(rbind, plot_list)
  for (i in 1:length(plot_df$day))
  {
    plot_df$day[i] <- clean_date_mdy(plot_df$day[i])
  }
  day_of_the_week <- 1:7
  dailyViews <- vector("numeric")
  for (i in 1:length(day_of_the_week))
  {
    day_df <- dplyr::filter(plot_df, day == day_of_the_week[i])
    dailyViews[i] <- sum(day_df$totalViews)
  }
  out_df <- data.frame(day_of_the_week, dailyViews, stringsAsFactors = F)
  g2 <- ggplot(data=out_df) + geom_point(mapping=aes(x=day_of_the_week,
                                                     y=dailyViews))+
  geom_smooth(mapping=aes(x=day_of_the_week, y=dailyViews))
  return(g2)
}

clean_date_num <- function(date)
{
    yr <- substr(date, 1, 2)
    dy <- substr(date, 4, 5)
    mo <- substr(date, 7, 8)
    out_date <- paste(mo, "/", dy, "/", yr, sep="")
    out_date <- out_date %>% mdy
    num_date <- out_date %>% as.numeric - 17483
    return(num_date)
}

clean_date_mdy <- function(date)
{
    yr <- substr(date, 1, 2)
    dy <- substr(date, 4, 5)
    mo <- substr(date, 7, 8)
    out_date <- paste(mo, "/", dy, "/", yr, sep="")
    out_date <- out_date %>% mdy
    out_date <- wday(out_date)
    return(out_date)
}

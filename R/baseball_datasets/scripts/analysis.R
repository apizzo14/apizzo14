plot_df <- Map(function(thisYear){
  year_df <- dplyr::filter(df, year == thisYear)
  year <- thisYear
  avg_sal <- mean(year_df$salary.adjusted)
  avg_era <- mean(year_df$ERA.adjusted, na.rm = TRUE)
  out_df <- data.frame(year= thisYear, 
                       salary.average= avg_sal, 
                       ERA.average =avg_era, 
                       stringsAsFactors = F)
  return(out_df)
}, unique(df$year))

plot_df <- do.call(rbind, plot_df)

g <- ggplot(data=plot_df) +
  geom_point(mapping=aes(x=factor(year),
                         y=salary.average))

g2 <- ggplot(data=plot_df) +
  geom_point(mapping=aes(x=ERA.average,
                         y=salary.average))

g3 <- ggplot(data=plot_df) +
  geom_point(mapping=aes(x=factor(year),
                         y=salary.average,
                         size = ERA.average))

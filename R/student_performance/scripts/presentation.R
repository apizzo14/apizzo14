library(ggplot2)

#boxplot showing difference in average score for each of three subjects
plot_gender <- function(d)
{
  p <- ggplot(d, aes(x = gender, y= math.score)) + geom_boxplot(outlier.colour="red") + 
    labs(title="Math Score by Gender",x="gender", y = "math score")
  print(p)
  p <- ggplot(d, aes(x = gender, y= reading.score)) + geom_boxplot(outlier.colour="red")+
    labs(title="Reading Score by Gender",x="gender", y = " reading score")
  print(p)
  p <- ggplot(d, aes(x = gender, y= writing.score)) + geom_boxplot(outlier.colour="red")+
    labs(title="Writing Score by Gender",x="gender", y = "writing score")
  print(p)
}

plot_reading_writing <- function(d)
{
  p <- ggplot(d, aes(x = reading.score, y = writing.score)) + geom_point(size=1)+
    labs(title="Reading Score vs Writing Score", x = "reading score", y = "writing score")+
    geom_smooth()
  print(p)
}
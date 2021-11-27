library(plyr)
library(dplyr)
library(igraph)

source("configuration.R")

employee1 <- "love-p"
employee2 <- "may-l"
employee3 <- "grigsby-m"
employee4 <- "cash-m"
employee5 <- "giron-d"

employees <- c(employee1, employee2, employee3, employee4, employee5)
# employee_names <-
le <- employees %>% length
# for (n in 1:le)n
# {
#   employees[n] <- Employee(employees[n]) %>% get_name.Employee()
# }
m <- matrix(rep(0, 25), nrow = 5, ncol = 5)
colnames(m) <- employees
rownames(m) <- employees

for (i in 1:le)
{
  e <- Employee(employees[i])
  #browser()
  num_emails_sent <- get_number_of_emails.Employee(e)
  sent_to <- list()
  for (i2 in 1:num_emails_sent)
  {
    file <- dir(e)[i2]
    path <- paste(e, file, sep = "")
    email <- Email(path)
    sent_to[[i2]] <- to.Email(email)
  }
  sent_to <- unlist(sent_to)
  other_employees <- setdiff(employees, employees[i])
  loe <- other_employees %>% length
  for (i3 in 1:loe)
  {
    emp <- Employee(employees[i3])
    employee_name <- get_name.Employee(emp)
    num_emails <- grep(employee_name, sent_to) %>% length
    m[employees[i], other_employees[i3]] <- num_emails
  }
}
print(m)
g <- igraph::graph_from_adjacency_matrix(m, weighted = T)
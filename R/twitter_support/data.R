library(plyr)
library(dplyr)
library(data.table)
library(ggplot2)

load_dataset <- function()
{
  d <- data.table::fread("../../datasets/twitter support dataset/twcs.csv",
                         sep=",",
                         header=T,
                         stringsAsFactors = F)
  return(d)
}

get_all_companies <- function()
{
  d <- data.table::fread("../../datasets/twitter support dataset/twcs.csv",
                         sep=",",
                         header=T,
                         stringsAsFactors = F)
  company_ndx <- d$inbound == FALSE
  # grepping on alphabet: grepl("[[:alpha:]]", d$author_id)
  company_vec <- d$author_id[company_ndx] %>% unique
  return(company_vec)
}







#class Company

construct.Company <- function(d, company_name)
{
  tweet_ndx <- d$author_id == company_name | grepl(company_name, d$text)
  company_tweets <- dplyr:: filter(d, tweet_ndx)
  return(company_tweets)
}

get_number_of_conversations.Company <- function(comp)
{
  authors <- comp$author_id %>% unique
  numeric_string_ndx <- grepl("[[:digit:]]", authors)
  authors <- authors[numeric_string_ndx]
  num_convos <- authors %>% length
  return(num_convos)
}

get_conversation.Company <- function(comp, i)
{
  authors <- comp$author_id %>% unique
  numeric_string_ndx <- grepl("[[:digit:]]", authors)
  authors <- authors[numeric_string_ndx]
  conv_with <- authors[i]
  conv_ndx <- comp$author_id == conv_with | grepl(conv_with, comp$text)
  out_df <- dplyr::filter(comp, conv_ndx)
  #conversation <- sort_convo(out_df)
  return(out_df)
}


sort_convo <- function(convo_df)
{
  sorted_list <- list()
  ndx <- is.na(convo_df$in_response_to_tweet_id)
  ndx_row <- dplyr::filter(convo_df, ndx)
  sorted_list[[1]] <- ndx_row
  # while (ndx_row$response_tweet_id != "")
  for (i in 1:(nrow(convo_df)-1)) #maybe try while ndx_row$response_tweet_id is not empty
  {
    to_find <- strsplit(ndx_row$response_tweet_id, ",")
    find_this <- to_find[[1]][1]
    ndx <- grepl(find_this, convo_df$tweet_id)
    ndx_row <- dplyr::filter(convo_df, ndx)
    sorted_list[[i+1]] <- ndx_row
  }
  out_df <- do.call(rbind, sorted_list)
  out_df <- dplyr::select(out_df, author = author_id, text)
  return(out_df)
}

VirAtl_longest_conv <- function(d)
{
  VirAtl <- construct.Company(d, "VirginAtlantic")
  VirAtl_convos <- get_conv_lengths(VirAtl)
  max_convo <- which.max(VirAtl_convos$conv.length)
  out_convo <- get_conversation.Company(VirAtl, max_convo)
  return(out_convo)
}

get_conv_lengths <- function(comp)
{
  customers <- comp$author_id %>% unique
  numeric_string_ndx <- grepl("[[:digit:]]", customers)
  customers <- customers[numeric_string_ndx]
  count_list <- list()
  for (i in 1:length(customers))
  {
    user_id <- customers[i]
    convos_ndx <- comp$author_id == user_id | grepl(user_id, comp$text)
    convos <- comp$author_id[convos_ndx]
    out_df <- data.frame(conv = i, conv.length = convos %>% length, 
                         stringsAsFactors = F)
    count_list[[i]] <- out_df
  }
  out_df <- do.call(rbind, count_list)
  return(out_df)
}

max_min_convo <- function(d)
{
  companies <- get_all_companies()
  companies <- setdiff(companies, "AmericanAir")
  avg_length <- Map(function(thisCompany){
    comp <- construct.Company(d, thisCompany)
    conv_df <- get_conv_lengths(comp)
    avg_num <- mean(conv_df$conv.length)
    out_df <- data.frame(company = thisCompany, avg.conv.length = avg_num,
                         stringsAsFactors = F)
    print(head(out_df))
    return(out_df)
  }, companies)
  mmconvo <- do.call(rbind, avg_length)
  return(mmconvo)
}

max_df <- function(companies_avg)
{
  max_ndx <- which.max(companies_avg$avg.conv.length)
  max <- companies_avg$company[max_ndx]
  return(max)
}

min_df <- function(companies_avg)
{
  min_ndx <- which.min(companies_avg$avg.conv.length)
  min <- companies_avg$company[min_ndx]
  return(min)
}

test_comp <- function(comp)
{
  customers <- comp$author_id %>% unique
  numeric_string_ndx <- grepl("[[:digit:]]", customers)
  customers <- customers[numeric_string_ndx]
  print(customers %>% length)
  for (i in 1:length(customers))
  {
    print(i)
    user_id <- customers[i]
    convos_ndx <- comp$author_id == user_id | grepl(user_id, comp$text)
    convos <- comp$author_id[convos_ndx]
    print(convos %>% length)
  }
}

# This program reads the labeled results file (from convert_mturk_results),
# and filters the original sample (created from sample_phrases) to only include
# tweets with a task based agreement of 1.0

# The output file can then be input to the wordcounts program


import numpy as np
import pandas as pd

#input file, labeled csv
input_file_labeled = "../myth_Hydroxychloroquine_sample_100_101921-labeled.csv"

#input file, original sample from sample_phrases.py
input_file_sample = "../Hydroxychloroquine_April6.csv"

#output file name
output_file_name = "../myth_Hydroxychloroquine_high_task_based.csv"


labeled_results = pd.read_csv(input_file_labeled)
high_tba_df = labeled_results[labeled_results.myth_score == 1.0]
high_tba_ndx = high_tba_df.tweet_id

tweet_sample_df = pd.read_csv(input_file_sample)
output_df = tweet_sample_df[tweet_sample_df.id_str.isin(high_tba_ndx)]

#write csv file
output_df.to_csv(output_file_name, sep = ',', index = False)

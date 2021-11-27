
# Test program to load two sampled csv files and manipulate them
# so that they can be used as negative tweets to build the classifiers
# with positive 5G tweets


import numpy as np
import pandas as pd

#read and combine negative tweet samples
#input file
neg_input_file1 = "../myth_origins_sample_100_032521-labeled.csv"

#input file
neg_input_file2 = "../myth_weather_sample_100_050621-labeled.csv"

neg_df1 = pd.read_csv(neg_input_file1)
neg_df2 = pd.read_csv(neg_input_file2)
#neg_df3 = pd.concat([df1.reset_index(drop=True), df2], axis=1)
total_neg_df = pd.concat([neg_df1, neg_df2])

neg_high_tb_df = total_neg_df[total_neg_df.myth_score == 1.0]
# for i in high_tb_df.count():
#     high_tb_df.myth_score[i] = 0
#     high_tb_df.myth_supports_score = 0
neg_high_tb_df = neg_high_tb_df.assign(myth_score = 0, myth_supports_score = 0)
#high_tb_df = high_tb_df.assign(myth_supports_score = 0)
#print(neg_high_tb_df)

#read and filter positive tweets
fvg_tweet1 = "../5G/myth_5G_sample_100_101921-labeled.csv"
fvg_tweet2 = "../5G/myth_5G_sample_100_151121-labeled.csv"

pos_df1 = pd.read_csv(fvg_tweet1)
pos_df2 = pd.read_csv(fvg_tweet2)

fvg_df = pd.concat([pos_df1, pos_df2])
#fvg_high_tb_df = pos_df1[pos_df1.myth_score == 1.0] #change to combined df

pos_neg_df = pd.concat([fvg_df, neg_high_tb_df])
print(pos_neg_df)



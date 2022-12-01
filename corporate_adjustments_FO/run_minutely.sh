#!/bin/sh

search_dir="/home/data/nsedata/MINUTELY/FUT/2022/"
updated_dir="new/2022/"

mkdir $updated_dir

for t0 in `ls $search_dir`; do
        ./minutely_data_copr_action_adjuster.out $search_dir $updated_dir $t0 corporate_actions_adj_factor_20221201.csv NSE_Symbol_Changes_20221201.csv
        echo "Processed $t0"
done
echo "All Processed!"

search_dir="/home/data/nsedata/MINUTELY/FUT/2021/"
updated_dir="new/2021/"

mkdir $updated_dir

for t0 in `ls $search_dir`; do
	./minutely_data_copr_action_adjuster.out $search_dir $updated_dir $t0 corporate_actions_adj_factor_20221201.csv NSE_Symbol_Changes_20221201.csv
	echo "Processed $t0"
done
echo "All Processed!"

search_dir="/home/data/nsedata/MINUTELY/FUT/2020/"
updated_dir="new/2020/"

mkdir $updated_dir

for t0 in `ls $search_dir`; do
        ./minutely_data_copr_action_adjuster.out $search_dir $updated_dir $t0 corporate_actions_adj_factor_20221201.csv NSE_Symbol_Changes_20221201.csv
        echo "Processed $t0"
done
echo "All Processed!"

search_dir="/home/data/nsedata/MINUTELY/FUT/2019/"
updated_dir="new/2019/"

mkdir $updated_dir

for t0 in `ls $search_dir`; do
        ./minutely_data_copr_action_adjuster.out $search_dir $updated_dir $t0 corporate_actions_adj_factor_20221201.csv NSE_Symbol_Changes_20221201.csv
        echo "Processed $t0"
done
echo "All Processed!"

search_dir="/home/data/nsedata/MINUTELY/FUT/2018/"
updated_dir="new/2018/"

mkdir $updated_dir

for t0 in `ls $search_dir`; do
        ./minutely_data_copr_action_adjuster.out $search_dir $updated_dir $t0 corporate_actions_adj_factor_20221201.csv NSE_Symbol_Changes_20221201.csv
        echo "Processed $t0"
done
echo "All Processed!"

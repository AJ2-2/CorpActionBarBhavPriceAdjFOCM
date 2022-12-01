#!/bin/sh

search_dir="/home/data/bhav_files/FO/"

updated_dir="./new_bhav/"
mkdir $updated_dir

for t0 in `ls $search_dir`; do
	./bhav_copr_action_adjuster.out $search_dir $updated_dir $t0 corporate_actions_adj_factor_20221201.csv NSE_Symbol_Changes_20221201.csv
	echo "Processed $t0"
done
echo "All Processed!"

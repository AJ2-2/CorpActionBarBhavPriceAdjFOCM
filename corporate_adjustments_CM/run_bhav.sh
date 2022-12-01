#!/bin/sh

search_dir="/home/data/bhav_files/CM/"

updated_dir="./new_bhav/"
mkdir $updated_dir

for t0 in `ls $search_dir`; do
	./bhav_copr_action_adjuster.out $search_dir $updated_dir $t0 tcp_ids_corp_factors_with_PEL_adjusted.csv NSE_Symbol_Changes.csv
	echo "Processed $t0"
done
echo "All Processed!"

#!/bin/sh

search_dir="old/"
updated_dir="new/"

mkdir $updated_dir

for t0 in `ls $search_dir`; do
	./minutely_data_copr_action_adjuster.out $search_dir $updated_dir $t0 tcp_ids_corp_factors_with_PEL_adjusted.csv NSE_Symbol_Changes.csv
	echo "Processed $t0"
done
echo "All Processed!"

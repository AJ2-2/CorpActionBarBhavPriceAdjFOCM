#!/bin/sh

search_dir="./old"
updated_dir="./new"

for t0 in `ls $search_dir`; do
	./bhav_copr_action_adjuster.out $t0 tcp_ids_corp_factors.csv 
	echo "Processed $t0"
done
echo "All Processed!"

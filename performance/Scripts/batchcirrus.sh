#!/bin/bash
#Author: B159973
#Automated script for running on Cirrus
# on proccess and grids below. 
p=(1 2 4 8 16 32 64 100 140 160 200)
grids=(100 400 800 1000 1600 3200 1000 5000 10000)
rm results
rm res.tsv


for l in "${grids[@]}"
do
	for pr in "${p[@]}"
	do 
		echo -e "Setting grid to mpirun \"$type,$chunk\" \\n" >>results
		printf "%s_%s_Total\t%s_%s_Update\n" "$l" "$pr" "$l" "$pr" >> res.tsv
		for reps in {1..3}
		do
			echo -e "\n==================Start===================\n" >>results
			mpiexec_mpt -ppn 36 -n $pr ./percolate  -l $l -m 1 -s 1564 -p map.pgm -r 0.5 > result
			cat result >> results

			resultTotal=`awk '/RANK  0/&&/Total/{print $12}' result`
			resultUpdate=`awk '/RANK  0/&&/Update/{print $12}' result`
			
			printf "%s\t%s\n" "$resultTotal" "$resultUpdate" >>res.tsv
			
			echo -e "\n==========Repetition $reps finished========\n" >>results
		done
		printf "\n" >> res.tsv
	done
done
cat res.tsv
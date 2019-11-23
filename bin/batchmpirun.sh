#!/bin/bash

#Author: B159973
#For grapping step
rho=0.5
p=(2 4)
grids=(5000)
rm results
rm res.tsv


for l in "${grids[@]}"
do
	for pr in "${p[@]}"
	do 
		echo -e "Setting grid to mpirun \"$type,$chunk\" \\n" >>results
		printf "%s_%s_Total\t%s_%s_Update\n" "$l" "$pr" "$l" "$pr" >> res.tsv
		for reps in {1..1}
		do
			echo -e "\n==================Start===================\n" >>results
			mpirun -n $pr ./percolate  -l $l -m 1 -s 1564 -p map.pgm -r 0.5 > result
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
#!/bin/bash
#B159973 - Programming Skills - 2019

typeset -A con
#DEFAULT values.If not specifing in the perc.conf the value that you want.
con=( 
    [size_l]=50
    [rho]=0.5
    [seed]=1000
    [max_clusters]=50
    [pgm_file]=map.pgm
    [nproc]=1
)

while read ln
do
    if echo $ln | grep -F = &>/dev/null
    then  #For each, parameters check if its in the perc.conf else use default
        field=$(echo "$ln" | cut -d '=' -f 1) 
        con[$field]=$(echo "$ln" | cut -d '=' -f 2-)
    fi
done < perc.conf
# Call the executable with the parameters. 
mpirun -n ${con[nproc]} ./percolate  -l ${con[size_l]} -m ${con[max_clusters]} -s ${con[seed]} -p ${con[pgm_file]} -r ${con[rho]} 
#!/bin/bash

# @Author: B159973
# @Date:   26/11/2019
# @Course: MPP - 2019
# @University of Edinburgh

typeset -A con
#DEFAULT values.If not specifing in the perc.conf the value that you want.
con=( 
    [nproc]=1
    [size_l]=288
    [rho]=0.411
    [seed]=1564
    [max_clusters]=1
    [pgm_file]=map.pgm
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

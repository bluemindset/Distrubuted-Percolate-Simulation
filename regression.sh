#!/bin/bash

# @Author: B159973
# @Date:   26/11/2019
# @Course: MPP - 2019
# @University of Edinburgh

# Testing Serial and Parallel versions

# From 1 to 32 proccesses the below configuration 
# which is the same as the serial version 
# and test each time the map.pgm output with the serial's version

nProc=32

serial_l=288
serial_seed=1564
serial_max_clust=1
serial_map_name=map.pgm
serial_rho=0.4110

for i in $(seq 1 $nProc); 
do

 mpirun -n $i ./bin/percolate -l $serial_l -m $serial_max_clust -s $serial_seed -p $serial_map_name -r $serial_rho
 mv map.pgm map$i.pgm
 mv map$i.pgm test/output

done

# Pytest will perform 32 tests

PYTHONPATH=src:lib pytest --junit-xml=test/report.xml test/test_regression.py

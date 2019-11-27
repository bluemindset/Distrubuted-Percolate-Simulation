
##### Message Passing Programming 2019 - Semester 1
##### Student Exam Number: B159973
##### University of Edinburgh @ 2019- 2020

# Percolate Parallel Version 
## Assignment Introduction

By employing message-passing parallel techniques and extensively use MPI tools, the percolate program must run successfully on multiple processes. The program description can be found [here](ext/MPP-coursework.pdf).

## Dependencies
#### MPICC
The program needs mpicc, the portable implementation of MPI in order to compile and link. Please install the mpicc compiler [MPICH](https://www.mpich.org/static/docs/latest/www1/mpicc.html).
The following version can run the program:
```sh
$ mpicc -v
  version 4.8.5 (GCC) 
```
On @Cirrus the user must perfrom the following in the root folder of the project
```sh
$ module load intel-compilers-18
$ module load mpt
```

## Install

#### Makefile:
The program is builded  completely via make. First it compiles the`*.c` files found in `/src` folder and then moves the object files under the `/obj` folder. After than it links the files together and produces the binary executable  in `/bin` folder under the name `percolate.exe`. 
There are several commands that makefile can take. All the commands must run inside the **project root directory** where the `Makefile `is located.
To **build** the program run the following:
```sh
$ make all
```
To **clean** the  `*.o` object files and the executable under `/obj` and the executable along with its output, issue:
```sh
$ make clean
```
To **print**  variables of the makefile issue:
```sh
$ make print
```
**Help** menu of makefile:
```sh
$ make help
```
## Run

#### Run executable
After the make command, the program can run via `run.sh` which is located in`\bin`folder:
```sh
$ cd bin
$ chmod +x  run.sh
$ chmod +rw perc.conf
$ ./run.sh
```
The run file first takes the values from the configuration file `perc.conf`  which is located in`\bin`folder. Please insert the values in the file first and then run `run.sh` .If no values are found then the run file uses default values: 
```sh
nproc=1
size_l= 288
rho= 0.411
seed= 1564 
max_clusters= 1
pgm_file= map.pgm
```

#### Manually
To run the program do the following:
```sh
$cd bin 
$ mpirun -n [number of processors]  ./percolate -l [grid size]  -s [seed]  -r [rho]  -m [max clusters]  -p [filename.pgm] 
```

##### Parameters:

It is very **important** to enter the parameters in the corect form. The program will not run if it detects parameters with wrong formats or exceeding lenghts:

1.  **Number of Processors** : A reasonable amount of processors to run on.

2.  **Grid Size** : Must be an positive integer, up to `9` digits. Allocation of a huge map may crush the system.

3. **Seed**: Must be an integer between `0` and `900,000,000`

4. **Rho**: Must be a valid fraction between` 0` and `1` with one dot. (ex: 0.5) and up to 9 digits.

5. **Max Clusters**:  Must be an positive integer, not exceeding (grid size * grid size).

6. **PGM filename**: A valid filename without these characters` %^!~|@*><`. It must also end with `.pgm` 

## Outputs
The program outputs a **.pgm file** inside the `\bin`folder. The **pgm file** is an image of the clusters and you can see the percolation.
To display the **pgm file** run: 
```sh
$display  filename.pgm
```

## Regression Test

Regression Test was implemented using regression tests package of Python [Python test framework](https://docs.python.org/2/library/test.html#module-test)
It is crucial to mention that for this particular test, we assume that Version 1 of the program, was the original one that was handed by the examiner [serial version].
Moreover, we assume that the new refactored version is the one that was given back to the examiner.[parallel version]
We do not assume that Version 2 perseveres **functional correctness** and therefore its output must be compared for equality with Version 1. 

#### Composition of the Regression Test
The testing structure has three components: 
1. The python unit test `test_regression.py` which is found in `\test` folder
2. A helper library, `regression.py` which peforms compilation and execution of the above instances, along with output gathering. It is located under `\lib` folder.
3. A batch script, `regression.sh` that calls the unit test with the helper library. It is located in the `root` directory.
4. The above test cases are found in `test` folder under the same instance name in Version 1 & 2. 

#### Run the Regression Test

Perform these commands to run the regression test in the `root` directory. The test takes on average about 30 seconds to one minute to complete because for each instance percolate must run.

```sh
$ chmod +x regression.sh
./regression.sh
```
### Report

The regression test generates a report that is under `test` with the name `report.xml`. The report shows that
the regression test is successful at the first line and prints the standard output of the executions of each instance. 

## Perfromance

The folder `performance` contains:
1. Python plots that were used in the report.
2. Runtimes of parallel percolate on @Cirrus.
3. Batch Scripts that automated executions on @Cirrus. 
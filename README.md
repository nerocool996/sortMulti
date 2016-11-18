# sortMulti
A program that merge sorts an array in multiple threads
The are two c file thrSort.c and thrSortN.c, first file impliment merge sort in multiple threads and the next one normally sorts the an array. 

# How to compile
Both the files can be compiled via gnu's compiler.
eg.
 ```
 gcc thrSort.c -pthread -o com1
 gcc thrSort.c -pthread -o com2
 ```
 Will create two object file com1 and com2 which can be executed with ' ./' command.
 
# Performance difference
For sorting and array of size 30000 normal merge sort took 0.011300 - 0.035980 seconds where as multithreaded merge sort took 0.007291 - 0.017000 seconds on a dual core i7 clocked at 3ghz .
Which is around 50% of speed improvement. 

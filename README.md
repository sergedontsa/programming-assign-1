COMP-428-ASSIGNMENT-1

In the programming part of this assignment, you will be solving an “embarrassingly” parallel problem, with minimal communication overhead and minimal I/O requirement. The main objectives are to make yourself familiar with MPI programming on the cluster, and also make you familiar with performance measurement.
Q.1. An approximate algorithm for calculating the value of  (PI) and its parallel version using the Master-Worker paradigm are provided towards the end of the tutorial that we discussed in the first class. Here is a link to the tutorial:
https://computing.llnl.gov/tutorials/parallel_comp/
The pseudo-code and C code that uses MPI are also provided in the tutorial. Here is what you are required to do:
a) Write a sequential version of the algorithm and execute it on a single node of the cluster. Measure the execution time. (Note: For fairness of performance comparison, a sequential and parallel version must do equal amount of “total computational work”, ignoring any other overheads.)
b) Execute the parallel version of the given program with varying number of workers (e.g. 2, 4, 6, etc) and measure the parallel execution time in each case. Ideally, workers should be mapped to distinct nodes of the cluster.
c) Referring to b), identify the tasks that are mapped to processes (Note: in this case, the master and each worker is a process). What determines the granularity of a task here?
d) In the given program b), the master and the worker processes are statically spawned. Another way to implement the program is to first create the Master process, which dynamically spawns the workers through explicitly calling MPI_Comm_Spawn. 
(i) Modify the given program accordingly to use this dynamic spawning mechanism available in the current versions of MPI. (ii) Solve the PI calculation problem based on the “Pool of Tasks” paradigm, which is one of the mechanisms often employed for dynamic load balancing. 
In the Pool of Tasks paradigm, the master and worker processes do the following: Master Process: o Holds pool of tasks for worker processes to do o Sends worker a task when requested o Collects results from workers Worker Process: repeatedly does the following o Gets task from master process

Assignment 1 – page 2 of 3
o Performs computation o Sends results to master
Hint: (1) You can think of an algorithm that keeps on computing  until it converges. So, in this case, the number of darts thrown (i.e. number of random numbers generated) is not fixed but varying until convergence occurs.
Execute the parallel version of the given program with varying number of workers (e.g. 2, 4, 6, etc.) as before and measure the parallel execution time in each case. Note that the sequential version must be changed accordingly for fair calculation of speedup.
e) Plot a speedup versus number of workers curve based on your experiments in (a) and (d) above. Explain any unusual behavior, e.g., slow down, sub-linear speedup, etc.

The run the program:
There are two parts in main.cpp class. Just comment one part and execute the following 
command from the  terminal
- ```mpicc main.cpp -o <name of the program>```
- ```mpirun <name of the program>``` is the number of the process # programming-assign-1

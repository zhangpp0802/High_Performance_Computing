# <center> Week 3 Assignments</center>

# Hands-On: Vector Normalization


 ## Analysis:

When the vectorsize raised to 1200, it seems like there's actually speed up for paralization.

For observation of run time:
* vector size = 200

| processor |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 0.273 |  1 |
| 2| 0.414 |  0.659 | 
| 3 | 0.311 |  0.878 | 
| 4 | 0.447 |  0.611 | 

For observation of run time:
* vector size = 1200

| processor |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 1.436 |  1 |
| 2| 1.29 |  1.113 | 
| 3 | 1.333 |  1.077 | 
| 4 | 1.275 |  1.126 | 

 # Parallelizing a 1-D Cellular Automaton

## Step 2: neighbor communication 

So I used the one you talked about in class. It would be able to send and then receive if myID in Distribute() is even, and vice versa. It would only use the basic MPI_Send and MPI_Recv we learned in week2.

## Step 4

Note:
You can try compile and run command line "mpirun -np 2 ./mpicell 50 40 126", which means the 50 bits, 40 operations in rule 126. If you only lack any of those parameters, the code would assume you have 128 bits, 100 operations in rule 30. If you only offers one or two parameters, it assume you only wanna customize the bits number or both the bits number and operation number.


For observation of run time:
* Here with Cell rule = 30 and iteration = 100.

| size |  serial(ms)| 2 processors  | speedup  |4  processors  | speedup  |
|----------|----------|:------------:|------:|:------------:|------:|
| 128| 1.43 |  3.49 | 0.42 | 3.30 | 0.44 |
| 160| 2.07 |  3.07 | 0.67 | 4.01 | 0.52 |
| 400 | 4.61 |  5.28 | 0.87 | 6.26 | 0.74 |
| 800 | 8.05 |  7.48 | 1.08 | 9.79 | 0.82 |

As size increasing, the speed upseems to perform better. Also, compared with 2 processors, 4 processors seem to have lower speedup rate. Time might cost more on four processors as to scatter, gather and other kinds of MPI operations.

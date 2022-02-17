
<center>Week 4: Advanced MPI</center>

# Vector Normalization round 2
* 
For observation of run time:
* vector size = 20

| processor |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 0.05 |  1 |
| 2| 0.27 |  0.19 | 
| 3 | 0.29 |  0.17 | 
| 4 | 0.43 |  0.12 | 

For observation of run time:
* vector size = 200

| processor |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 0.19 |  1 |
| 2| 0.50 |  0.38| 
| 3 | 0.62 |  0.31 | 
| 4 | 0.59 |  0.32 | 

For observation of run time:
* vector size = 1200

| processor |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 0.57 |  1 |
| 2| 1.07 |  0.53| 
| 3 | 0.82 |  0.70 | 
| 4 | 0.94 |  0.61 | 

# Vector Mean

Note: you can run with something like this:
 `$ mpirun -np 4 ./mean 200`
* This would be defautly run a random range of 0-100.
To have a upper range of the random integer:
 `$ mpirun -np 4 ./mean 200 1000`
* To have both upper and lower bound range of the random integer:
 `$ mpirun -np 4 ./mean 200 10 1000`
* Since I used rand() for randome a integer, it might overflow without bound which would give us a negative number. You can comment out line 36-45, and line 87-88; and uncomment line 89 to see the overflower result.

For observation of run time:
* vector size = 20

| processor |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 0.05 |  1 |
| 2| 0.26 |  0.19 | 
| 3 | 0.20 |  0.25 | 
| 4 | 0.28 |  0.18 | 

For observation of run time:
* vector size = 1200

| processor |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 0.06 |  1 |
| 2| 0.17 |  0.35| 
| 3 | 0.17 |  0.35 | 
| 4 | 0.25 |  0.24 | 

For observation of run time:
* vector size = 120000

| processor |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 2.22 |  1 |
| 2| 1.17 |  1.90 | 
| 3 | 0.98 |  2.34 | 
| 4 | 0.76 |  2.92 | 

As the vector size increased higher, the speed up become more efficient as more processors were adding in.

# Vector STD

* Note: you can run with something like this:
 `$ mpirun -np 4 ./std 200`
* This would be defautly run a random range of 0-100.
To have a upper range of the random integer:
 `$ mpirun -np 4 ./std 200 1000`
* To have both upper and lower bound range of the random integer:
 `$ mpirun -np 4 ./std 200 10 1000`
* Since I used rand() for randome a integer, it might overflow as adding and give a "nan" on the result which means the false on the double variables. You can comment out line 33-42, and line 85; and uncomment line 84 to see the overflower result.

For observation of run time:
* vector size = 20

| processor |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 0.05 |  1 |
| 2| 0.25 |  0.20 | 
| 3 | 0.38 |  0.13 | 
| 4 | 0.21 |  0.16 | 

For observation of run time:
* vector size = 1200

| processor |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 0.68 |  1 |
| 2| 0.58 |  1.17 | 
| 3 | 0.54 |  1.26 | 
| 4 | 0.49 |  1.39 | 

For observation of run time:
* vector size = 120000

| processor |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 35.66 |  1 |
| 2| 22.90 |  1.56 | 
| 3 | 21.90 |  1.63 | 
| 4 | 19.60 |  1.82 | 

As the vector size increased higher, the speed up become more efficient as more processors were adding in from even early than the vector mean.

# LOS

* Note: you can run with something like this:
 `$ mpirun -np 4 ./std 200` when try to processing 200 datapoints.

As shown above, it take less and less when the WORLDSIZE is less than 100000. However, as it try to reach 200000 WORLDSIZE, it spend more time than expected which should about 290ms (5*WORLDSIZE 10000) or 300ms (10*WORLDSIZE 20000). See some images in the "result" folder!
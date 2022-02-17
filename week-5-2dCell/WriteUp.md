
<center>Week 5: 2D Cell Aut</center>


Note: you can run with something like this:
 `$ mpirun -np 4 ./mean 200`
* This need to be divided by the number of processors

# SpeedUp and Efficiency

For observation of run time:
* size = 200

| processor |  time (ms)  | speedup  | efficency |
|----------|:------------:|------:|------:|
| 1| 30.334 |  1 | 1 |
| 2| 48.348 |  0.63 | 0.315 |
| 4 | 80.913 |  0.37 | 0.093 |

For observation of run time:
* size = 560

| processor |  time (ms)  | speedup  | efficency |
|----------|:------------:|------:|------:|
| 1| 430.334 |  1 | 1 |
| 2| 375.728 |  1.14 | 0.57 |
| 4 | 364.627 |  1.18 | 0.295 |


For observation of run time:
* size = 1200

| processor |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 2033.245 |  1 | 1 |
| 2| 1677.633 |  1.21 | 0.605 |
| 4 | 1541.325 |  1.32 | 0.33 |

It's quite obvious that as the size grows, the speedup performance is also better as the processors added. This might because when size is small, the communication time is larger than the calculation parallel time that actually speeded up. But as the size become larger, the communication time seems to worth for parallel the calculation.

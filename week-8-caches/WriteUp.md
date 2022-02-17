# Matrix Manipulation and Caches

Note: To see the result, you can uncomment line 103(rand matrix1), 105(rand matrix2), 116(for addition), and 125(for transpose) to print the original matrices and the calculated matrices out. Also, please run with same row and column like below:
* ./m 10 10
Also, below data are recording the time of the matrices addition and the transpose together.

## Time Analysis 

Non-schedule parallel (static with chunck size = 1):<br />
|  size  | time (s)  |
|:------------:|------:|
| 100 |  0.002350 |
| 500 |  0.208409 |
| 1000 |  0.768294 |
| 2000 |  3.269567 |
| 4000 |  13.140140 |
| 8000 |  52.686168 |

*Note: Below are for just thread numvber = 1*

Schedule Parallel (static with chunck size = 1):<br />

|  size  | time (s)  |
|:------------:|------:|
| 100 |  0.000331 |
| 500 |  0.002895 |
| 1000 |  0.009540 |
| 2000 |  0.039495 |
| 4000 |  0.155428 |
| 8000 |  0.624937 |

Schedule Parallel (static with chunck size = 10):<br />

|  size  | time (s)  |
|:------------:|------:|
| 100 |  0.000210 |
| 500 |  0.002349 |
| 1000 |  0.008557 |
| 2000 |  0.037829 |
| 4000 |  0.146005 |
| 8000 |  0.599824 |

Schedule Parallel (static with chunck size = 100):<br />

|  size  | time (s)  |
|:------------:|------:|
| 100 |  0.000246 |
| 500 |  0.002225 |
| 1000 | 0.008662 |
| 2000 |  0.036831 |
| 4000 |  0.136286 |
| 8000 |  0.631003 |


Schedule Parallel (dynamic with chunck size = 1):<br />

|  size  | time (s)  |
|:------------:|------:|
| 100 |  0.000294 |
| 500 |  0.003531 |
| 1000 |  0.011286 |
| 2000 |  0.049746 |
| 4000 |  0.165378 |
| 8000 |  0.663252 |

Schedule Parallel (dynamic with chunck size = 10):<br />

|  size  | time (s)  |
|:------------:|------:|
| 100 |  0.000104 |
| 500 |  0.002294 |
| 1000 |  0.008449 |
| 2000 |  0.039047 |
| 4000 |  0.141724 |
| 8000 |  0.636212 |

Schedule Parallel (dynamic with chunck size = 100):<br />

|  size  | time (s)  |
|:------------:|------:|
| 100 |  0.000263 |
| 500 |  0.002280 |
| 1000 |  0.007973 |
| 2000 |  0.033269 |
| 4000 |  0.135623 |
| 8000 |  0.629404 |

Mutithread(static with chunck size = 10):<br />
|  nthread  | time(s)  | speedup  | efficency |
|:------------:|------:|------:|------:|
| 1 |  0.008748 | 1 | 1 |
| 2 |  0.008423 | 1.039 | 0.519 |
| 3 |  0.008579 | 1.020 | 0.34 |
| 4 |  0.008515 | 1.027 | 0.257 |
| 5 |  0.009874 | 0.886 | 0.177 |
| 6 |  0.009118 | 0.960 | 0.16 |
| 7 |  0.008625 | 1.014 | 0.145 |
| 8 |  0.009440 | 0.926 | 0.116 |

Mutithread(dynamic with chunck size = 10 and row = col = 1000):<br />
|  nthread  | time(s)  | speedup  |
|:------------:|------:|------:|
| 1 |  0.008848 | 1 | 1 |
| 2 |  0.008337 | 1.061 | 0.53 |
| 3 |  0.008703 | 1.017 | 0.339 |
| 4 |  0.008369 | 1.057 | 0.264 |
| 5 |  0.008318 | 1.064 | 0.213 |
| 6 |  0.008584 | 1.031 | 0.172 |
| 7 |  0.008311 | 1.065 | 0.152 |
| 8 |  0.008787 | 1.007 | 0.126 |

Above are the run time for both static and dynamic with chuck sizes of 1, 10, and 100. Compare among static, it's obvious that as the chunck size get bigger, it would generally speed up. It might because no matter the chuck size is 1 10 or 100, each thread would execute the same node (in matrices). However, for chuck size = 1 or 10, static schedule would need more time on figuring out which node they should take since there're more chuncks when chunck size is relatively small. <br />

Then, for dynamic, it spends more time as chunck size grows. This might because for dynamic, each thread would get the next chunck as soon as they finish their current one. Thus, this might cause more of imbalanced work in each thread as the chuck size goes up. Though for chunksize = 100, and np = 4, matrix size = 8000 can be evenly divided, it might accidently have a thread that process more chuncks than others due to finishing previous chuncks earlier. Thus, this time imbalance among threads might cause time difference.<br />
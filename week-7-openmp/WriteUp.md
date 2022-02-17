# <center> Week 7 Assignments</center>

# Vector Operation


 ## Analysis:

For observation of run time:
* vector size = 10

| threads |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 0.185 |  1 |
| 2| 0.41 |  0.451 | 
| 3 | 0.411 |  0.45 | 
| 4 | 1.007 |  0.184 | 

* vector size = 1200

| threads |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 3.17 |  1 |
| 2| 4.722 |  0.671 | 
| 3 | 6.138 |  0.516 | 
| 4 | 6.341 |  0.5 | 


* vector size = 120000

| threads |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 122.221 |  1 |
| 2| 148.559 |  0.823 | 
| 3 | 173.705 |  0.704 | 
| 4 | 266.031 |  0.458 | 

For this problem, the speedup result become better as vector size is increased but even vectorsize is increased to 120000, calculation with multiple thread paralleling still cannot beat the one with one thread. Thus, paralleling with threads here is not quite helpful.

# Numerical Integration Estimation of Pi


 ## Analysis:

For observation of run time:
* n = 100

| threads |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 0.095 |  1 |
| 2| 0.205 |  0.463 | 
| 3 | 0.196 |  0.485 | 
| 4 | 0.348 |  0.273 | 

* n = 48000

| threads |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 1.993 |  1 |
| 2| 0.442 |  4.51 | 
| 3 | 0.890 |  2.24 | 
| 4 | 1.878 |  1.06 | 

* n = 120000

| threads |  time (ms)  | speedup  |
|----------|:------------:|------:|
| 1| 4.115 |  1 |
| 2| 4.073 |  1.01 | 
| 3 | 1.568 |  2.62 | 
| 4 | 2.388 |  1.723 | 


Among above data, it's abvious to see that the speedup is helpful as n is 48000. Also, it can always get a best speed up when the calculation splits on three threads (except for n = 48000). I'm not sure about why is that but as summary, it is normally able to have more efficient speed up as the n grows larger.



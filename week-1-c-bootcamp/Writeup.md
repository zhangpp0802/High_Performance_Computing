
<center>Yiran Zhang</center>

# Task List
- [*] Complete Setup (clone repos)
- [ ] Assignment 1: Factorization

# Assignment 1

PART I:
It would print "This is a prime" when the bignumber is a prime. If not, it would just return its largest factor. Any number being tested would return its run time of checking if that is prime or its largest factor.

PART II:
In the for loop, we check with i += 2 instead of 1 since odd number plus 1 is always even and even number >=3 can never be prime. 

# Assignment 1

I added "#SIZE += 2" to mess up the vector size. What I get is ten elements being printed out and the last one is always 0.000000. 

As I added the clock into vectors.c file and play around with it. I found it become slower when I try to set vector with size 30000000. 10000000 would take 410.826000 ms. 30000000 would take 1211.040000 ms.
70000000 would take 2865.013000 ms. When I tried to add more to 200000000, it took 13663.242000 ms, which means it's kinda stuck for a while.
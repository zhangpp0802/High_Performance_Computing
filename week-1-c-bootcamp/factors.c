#include <stdio.h>
#include <time.h>
#include <math.h>
#include <limits.h>

/*

*/ 


int main(int argc, char *argv[])
{

  //printf ("sizeof unsigned long: %lu",sizeof(unsigned long));
  //printf ("sizeof unsigned long long: %lu",sizeof(unsigned long long));
  unsigned long long bignumber = 4185633689926419098;
  // unsigned long long bignumber = 4185; // test 1395
  // unsigned long long bignumber = 43; // test prime
  unsigned long i;
  unsigned long max;
  max = 0;

  clock_t startTime = clock();
  for (i = 3; i <= sqrt(bignumber); i+=2)
  {
    if ((bignumber % i) == 0)
    {
      max = i;
      // printf("I found %lu\n",i);
      // break;
    }
  }
  if (max == 0)
    {
      printf("This is a prime. \n");
    }
  else{
    printf("I found the largest factor: %lu\n",max);
    }
  clock_t endTime = clock();
  double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
  printf("That took %f ms\n",elapsed);

  // I do not think stop at sqrt(bignumber) make sense, so below is the version that I think is right

  // for (i = 3; i <bignumber; i+=2)
  // {
  //   if ((bignumber % i) == 0)
  //   {
  //     max = i;
  //     // printf("I found %lu\n",i);
  //     // break;
  //   }
  // }
  // if (max == 0)
  //   {
  //     printf("This is a prime. \n");
  //   }
  // else{
  //   printf("I found the largest factor: %lu\n",max);
  //   }
  // clock_t endTime = clock();
  // double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
  // printf("That took %f ms\n",elapsed);
}

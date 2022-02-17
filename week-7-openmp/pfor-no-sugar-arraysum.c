#include <stdio.h>
#include <omp.h>
 
int main(int argc, char *argv[])
{
  int PiVals[10] = {3,1,4,1,5,9,2,6,5,4};
  int nthreads = 1;
  if (argc > 1)
	nthreads = strtol(argv[1],NULL,10);
	int globalsum = 0;

  #pragma omp parallel num_threads(nthreads)
{
	int myid = omp_get_thread_num();
	int threadcount = omp_get_num_threads(); //like, super-high threadcount sheets?
	int localsum = 0;
	for (int i = myid ; i < 10; i+=threadcount)
	{
		localsum += PiVals[i];
	}
	globalsum += localsum;
} 
#pragma omp critical 

printf("global sum is %d\n",globalsum);
}

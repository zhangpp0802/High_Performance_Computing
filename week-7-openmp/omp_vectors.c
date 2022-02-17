#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

/*
vectors.c for week 1 bootcamp
author: John Rieffel

*/

//argc is the argument count from the commandline
//argc is always at least 1, because the excutable
//is an argument
//
//each argument is held in a separate string.
//argv is an *array* of strings

// Note: Need to compile like this : gcc -I. -fopenmp omp_vectors.c   -o omp_vectors -lm

double * randomize_vector(double *vec, int size)
{
  int index;
  for (index= 0; index< size; index++ ) {
   vec[index] = drand48();
  }
  return vec;
}

void print_vector(double *vec, int size)
{
  int index;
  for (index= 0; index< size; index++ ) {
    printf("%f ", vec[index]);
}
  printf("\n");
  return;
}

void print_vector_p(double *vec, int size)
{
  double *p;
  double * vec_end = vec+size;
  for (p = vec; p < vec_end; p++)
  {
    printf("%f ", *p);
  }

}

void vector_add(double *v1, double* v2, double *result, int size, int nthreads)
{

  #pragma omp parallel num_threads(nthreads)
{
	int myid = omp_get_thread_num();
	for (int i = myid ; i < size; i+=nthreads)
	{
		result[i] = v1[i]+v2[i];
	}
} 
// #pragma omp critical
}

//return the mean of a vector
double vector_mean(double *v1, int size, int nthreads)
{
  double globalsum = 0;
  #pragma omp parallel num_threads(nthreads)
{
	int myid = omp_get_thread_num();
  double localsum = 0;
	for (int i = myid ; i < size; i+=nthreads)
	{
		localsum += v1[i];
	}
  globalsum += localsum;
}
    double mean = globalsum/size;
    return mean;

}

//return the magnitude of a a vector
// (squareroot of sum of squares )
double vector_mag(double *v1, int size, int nthreads)
{
  double globalsquare = 0;
  #pragma omp parallel num_threads(nthreads)
{
	int myid = omp_get_thread_num();
  double localsquare = 0;
	for (int i = myid ; i < size; i+=nthreads)
	{
		localsquare += v1[i]*v1[i];
	}
  globalsquare += localsquare;
}
    double mag = sqrt(globalsquare);
    return mag;
}

//normalize a vector, putting result in outv 
void vector_normalize(double *v1, double *outv, int size, int nthreads)
{
 //first a call to vector mag
 double mag = vector_mag(v1,size,nthreads);
 //then an omp for loop that divides evertying in the vector by magnitude
 #pragma omp parallel num_threads(nthreads)
{
	int myid = omp_get_thread_num();
	for (int i = myid ; i < size; i+=nthreads)
	{
		outv[i] = v1[i]/mag;
	}
}
 //warning don't ever omp parallelize loops that call functions that also parallelize 
}

int main(int argc, char *argv[])
{
  int SIZE = 10;
  int nthreads = 2;
  if (argc > 4){
    printf("usage: vectors <procs> <size> or vectors <procs> <size> <seed>\n ");
    exit(1);
  }
  else {
      if (argc > 1)
        nthreads = strtol(argv[1],NULL,10); 
      if (argc > 2)
        SIZE = atoi(argv[2]); //atoi converts a string to an int
      if (argc > 3)
        srand48(atoi(argv[3]));
      else
        srand48(time(NULL));
        
  }
  clock_t startTime = clock();
  printf("threads: %d, vector size: %d\n",nthreads,SIZE);

//calloc, unlike malloc, zeros the allocated memory
double * vector1 =  calloc(SIZE,sizeof(double));
double * vector2 =  calloc(SIZE,sizeof(double));
double * vector3 =  calloc(SIZE,sizeof(double));

vector1 = randomize_vector(vector1, SIZE);
vector2 = randomize_vector(vector2, SIZE);

printf("Vector1:\n");
print_vector(vector1,SIZE);
printf("\n");
printf("Vector2:\n");
print_vector(vector2,SIZE);
printf("\n");

vector_add(vector1,vector2,vector3,SIZE,nthreads);
printf("Adding Vectors:\n");
print_vector_p(vector3,SIZE);
printf("\n");
printf("\n");

double mean = vector_mean(vector1,SIZE,nthreads);
printf("Mean vector1: %f\n",mean);
printf("\n");
printf("\n");

double mag = vector_mag(vector1,SIZE,nthreads);
printf("Magnitude vector1: %f\n",mag);
printf("\n");
printf("\n");

vector_normalize(vector1,vector3,SIZE,nthreads);
printf("Normalize Vector1:\n");
print_vector_p(vector3,SIZE);
printf("\n");
printf("\n");

clock_t endTime = clock();
double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
printf("That took %f ms\n",elapsed);

}

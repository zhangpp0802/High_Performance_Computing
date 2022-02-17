#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <limits.h>

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

double * randomize_vector(double *vec, int size)
{
  int index;
  for (index= 0; index< size; index++ ) {
   vec[index] = drand48();
  }
  return vec;
}

// change only on pointer
void randomize_vector_p(double *vec, int size){
  int index;
  for (index= 0; index< size; index++ ) {
   vec[index] = drand48();
  }
}

void addition(double *vec1, int size1,double *vec2, int size2,double *sum){
  if (size1 == size2){
    int index;
    for (index= 0; index< size1; index++ ) {
      sum[index] = vec1[index]+vec2[index];
    }
  }
  else{
    printf("Two vectors are not the same size, and thus not able to add.");
  }

}

double dot(double *vec1, int size1,double *vec2, int size2){
  if (size1 == size2){
    int index;
    double dotproduct;
    for (index= 0; index< size1; index++ ) {
      dotproduct += vec1[index]*vec2[index];
    }
    return dotproduct;
  }
  else{
    printf("Two vectors are not the same size, and thus not able to calculate the dot product.");
    return DBL_MAX;
  }

}

void print_vector(double *vec, int size)
{
  int index;
  for (index= 0; index< size; index++ ) {
    printf("%f ", vec[index]);
}

  return;
}

void print_vector_p(double *vec, int size)
{
  double *p;
  double * vec_end = vec+size;
  for (p = vec; p < vec_end; p++)
  {
    printf("%f ", *p);
    printf("\n");
  }

}
int main(int argc, char *argv[])
{
  int SIZE = 0;

  if ((argc < 2) || (argc > 3)){
    printf("usage: vectors <size> or vectors <size> <seed>\n ");
    exit(1);
  }
  else {
      SIZE = atoi(argv[1]); //atoi converts a string to an int
      printf("size: %d\n",SIZE);
      if (argc == 3)
        srand48(atoi(argv[2]));
      else
        srand48(time(NULL));
  }

clock_t startTime = clock();

//calloc, unlike malloc, zeros the allocated memory
double * vector1 =  calloc(SIZE,sizeof(double));
double * vector2 =  calloc(SIZE,sizeof(double));

// mess up vector size
// SIZE += 2;
randomize_vector_p(vector1, SIZE);
randomize_vector_p(vector2, SIZE);

printf("Vector1 is:");
print_vector(vector1,SIZE);
printf("Vector2 is:");
print_vector(vector2,SIZE);

// test addition
double * sum =  calloc(SIZE,sizeof(double));
addition(vector1,SIZE,vector2,SIZE,sum);
printf("Addition is:");
print_vector(sum,SIZE);

// test dot
double dotproduct = dot(vector1,SIZE,vector2,SIZE);
printf("Dot product is %lf \n", dotproduct);

// added clock
clock_t endTime = clock();
double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
printf("That took %f ms\n",elapsed);

}

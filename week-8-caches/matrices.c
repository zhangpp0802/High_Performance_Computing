#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

// Note: Need to compile like this : gcc -I. -fopenmp matrices.c   -o m -lm

double * randomMatrix(double * m, int rows, int cols, int nthreads){
  unsigned short xi[3] = {1,9,99};
  int row,col;
  // #pragma omp parallel for schedule(static,1)
  
  #pragma omp parallel for schedule(static,10) private(row,col)
  // int myid = omp_get_thread_num();
	// for (int i = myid ; i < size; i+=nthreads)
  for (row = 0; row < rows; row++ ) {
    for (col = 0; col < cols; col++) {
      m[row*cols + col] = drand48();
    }
  }

  return m;
}

void matrixAdd(double * m1, double * m2,double * result,int rows, int cols,int nthreads){
  int row,col;
  // #pragma omp parallel for schedule(static,1)
  
  #pragma omp for schedule(static,10) private(row,col)
  // int myid = omp_get_thread_num();
  for (row = 0; row < rows; row++ ) {
    for (col = 0; col < cols; col++) {
      result[row*cols + col] = m1[row*cols + col]+m2[row*cols + col];
    }
  }
  

}

void matrixTrans(double * m1, double * result,int rows, int cols,int nthreads){
  int row,col;
  // #pragma omp parallel for schedule(static,1)
  
  #pragma omp parallel for schedule(static,10) private(row,col)
  for (row = 0; row < rows; row++ ) {
    for (col = 0; col < cols; col++) {
      result[col*cols + row] = m1[row*cols + col];
      // printf("%f\n",result[col*cols + row]);
    }
  }
  
}

void printMatrix(double * m1, int rows, int cols){
  int row,col;
  for (row = 0; row < rows; row++ ) {
  for (col = 0; col < cols; col++) {
      printf("%f ",m1[row*cols + col]);
  }
  printf("\n");
  }
}



int main(int argc, char *argv[])
{

  int ROWS = 0;
  int COLS = 0;
  int nthreads;
  // THIS WILL BE YOUR RANDOM SEED
  // YES IT IS NON-RANDOM - Read the lab!
  unsigned short xi[3] = {1,9,99};
  double somenum = erand48(xi);

  if (argc == 3){
      ROWS = atoi(argv[1]);
      COLS = atoi(argv[2]);
      printf("Rows: %d, Cols: %d\n",ROWS,COLS);
      nthreads = 1;
  }
  else if (argc == 4){
      ROWS = atoi(argv[1]);
      COLS = atoi(argv[2]);
      printf("Rows: %d, Cols: %d\n",ROWS,COLS);
      nthreads = atoi(argv[3]);;
  }
  else{
    printf("usage: matrices <rows> <cols>\n ");
    exit(1);
  }

  //double MAT[][] = calloc(ROWS*COLS,sizeof(double));

//double MAT[ROWS][COLS];
double * mat1 =  calloc(ROWS*COLS,sizeof(double));
double * mat2 =  calloc(ROWS*COLS,sizeof(double));
mat1 = randomMatrix(mat1,ROWS,COLS,nthreads);
mat2 = randomMatrix(mat2,ROWS,COLS,nthreads);
printf("matrix1 created \n");
// printMatrix(mat1,ROWS,COLS);
printf("matrix2 created \n");
// printMatrix(mat2,ROWS,COLS);


// addition
double * add =  calloc(ROWS*COLS,sizeof(double));
double start; 
double end; 
start = omp_get_wtime(); 
matrixAdd(mat1, mat2,add,ROWS, COLS,nthreads);
printf("Matrix Addtion \n");
// end = omp_get_wtime(); 
// printMatrix(add,ROWS,COLS);
// printf("Work took %f seconds\n", end - start);
// 
// transpose
double * trans =  calloc(ROWS*COLS,sizeof(double));
// start = omp_get_wtime(); 
matrixTrans(add,trans,ROWS, COLS,nthreads);
printf("Matrix Transpose \n");
end = omp_get_wtime(); 
// printMatrix(trans,ROWS,COLS);
printf("Work took %f seconds\n", end - start);



 //free(MAT); //don't FREE! C99 takes care of it if allocated like this
 //(instead of via malloc)
}

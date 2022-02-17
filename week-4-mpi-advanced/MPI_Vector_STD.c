#define _XOPEN_SOURCE 
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //for random seed
#include <math.h> //need to compile with -m
#include <time.h>
#include <limits.h>

//Note: Please run this file with "-lm" at the end; Otherwise, it would not work due to the sqrt().

//being explicit here to make code more readable
#define ROOT_NODE 0
//

int main(int argc, char *argv[]){


	int        comm_sz;               /* Number of processes    */
	int        my_rank;               /* My process rank        */
	//Don't put any MPI stuff before this line

	// double *bigVector;
	clock_t startTime = clock();

	double  *myVectorSlice;
	int upper;
	int lower;
	int BigVectorSize;
	if (argc == 2){
		BigVectorSize = atoi(argv[1]);
		upper = 100;
		lower = 0;
	}
	else if (argc == 4){
		BigVectorSize = atoi(argv[1]);
		lower = atoi(argv[2]);
		upper = atoi(argv[3]);
	}
	else if (argc == 3){
		BigVectorSize = atoi(argv[1]);
		upper = atoi(argv[2]);
		lower = 0;
	}
	else{
		upper = 100;
		lower = 0;
		BigVectorSize = 200;
	}

	MPI_Init(&argc, &argv);  //sets up the MPI. Always this line!

	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  //for now, make these evenly divisible.
	//later, we'll cover ScatterV
	int myVectorSliceSize;

	// comm_sz -= 1;
	if (BigVectorSize%comm_sz == 0){
		myVectorSliceSize = BigVectorSize/comm_sz;
	} 
	else{
		myVectorSliceSize = BigVectorSize/comm_sz+1;
	}

	if ((BigVectorSize%comm_sz) != 0)
	{
		printf("Can't do this with this number of processes\n");
	}

	// printf("myVectorSliceSize: %d",myVectorSliceSize);


//dynamically allocate a vector to hold our personal slice of the data
myVectorSlice = malloc(myVectorSliceSize*sizeof(double));
int localSum;

//get local sum out from rand()
localSum = 0;

for (int index= 0; index< myVectorSliceSize; index++ ) {
	srand(time(NULL) );
	// int r = rand();
	int r = (rand() % (upper - lower + 1)) + lower;
	localSum += r;
	myVectorSlice[index] = r;
	localSum += r;
  }

int sum;
// gather all and get mean

MPI_Allreduce(&localSum,&sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);

double localCal = 0;

for (int index= 0; index< myVectorSliceSize; index++ ) {
	
	localCal += (myVectorSlice[index]-sum)*(myVectorSlice[index]-sum);
  }

double calcu;
MPI_Reduce(&localCal,&calcu,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

if (my_rank == 0)
{	
	double cal = sqrt(sum / BigVectorSize);
	printf("The Vector Standard Deviation is: %f \n", cal);
	clock_t endTime = clock();
	double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
	printf("That took %f ms\n",elapsed);

}



MPI_Finalize();
//finito!
	//please no MPI stuff after this line
return 0;
}

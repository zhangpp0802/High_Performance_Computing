#include <mpi.h>
#include <stdio.h>
//to compile: mpicc -std=c99 -Wall MPI_blank_template.c -o MPI_blank
//to run (simple): mpirun ./MPI_blank

int main(int argc, char *argv[]){


	int        comm_sz;               /* Number of processes    */
	int        my_rank;               /* My process rank        */
	//Don't put any MPI stuff before this line

	int ArraySize = 233;
	short SomeBigArray[233] = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8,4,1,9,7,1,6,9,3,9,9,3,7,5,1,0,5,8,2,0,9,7,4,9,4,4,5,9,2,3,0,7,8,1,6,4,0,6,2,8,6,2,0,8,9,9,8,6,2,8,0,3,4,8,2,5,3,4,2,1,1,7,0,6,7,9,8,2,1,4,8,0,8,6,5,1,3,2,8,2,3,0,6,6,4,7,0,9,3,8,4,4,6,0,9,5,5,0,5,8,2,2,3,1,7,2,5,3,5,9,4,0,8,1,2,8,4,8,1,1,1,7,4,5,0,2,8,4,1,0,2,7,0,1,9,3,8,5,2,1,1,0,5,5,5,9,6,4,4,6,2,2,9,4,8,9,5,4,9,3,0,3,8,1,9,6,4,4,2,8,8,1,0,9,7,5,6,6,5,9,3,3,4,4,6,1,2,8,4,7,5,6,4,8,2,3,3,7};
	MPI_Init(&argc, &argv);  //sets up the MPI. Always this line!


	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	// do some stuff

	int i;
    int localsum = 0;
	int globalsum = 0;

	int for_each_process = (int) ArraySize/comm_sz;
	int remainder = ArraySize % comm_sz;
	int my_first_i;
	int my_last_i;
	int m = 0;


	if (my_rank < remainder){
		my_first_i = my_rank*(for_each_process+1);
		my_last_i = my_first_i+for_each_process+1;
	}
	else{
		my_first_i = remainder*(for_each_process+1)+(my_rank-remainder)*for_each_process;
		my_last_i = my_first_i+for_each_process;
	}
	printf("first and last sum of process %d is %d, %d\n",my_rank,my_first_i,my_last_i);
	for(i = my_first_i; i< my_last_i;i++){
		localsum+=SomeBigArray[i];
		m++;
		// printf("now adding %d to %d\n",SomeBigArray[i],my_rank);
		// printf("local sum of process %d is %d\n",my_rank,localsum);
	}
	// printf("m is %d", m);
	printf("local sum of process %d is %d\n",my_rank,localsum);

	if (my_rank != 0) {

		MPI_Send(&localsum,1,MPI_INT,0,0,MPI_COMM_WORLD);
	}
	else
	{
		int q;
		int othersum;

		globalsum = localsum;

		for (q = 1; q < comm_sz; q++)
		{
					MPI_Recv(&othersum,1,MPI_INT,q,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
					globalsum += othersum;
		}

		printf("the total sum is %d\n", globalsum);
	}


	MPI_Finalize();
	//please no MPI stuff after this line
	return 0;
}

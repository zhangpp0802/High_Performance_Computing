#define _XOPEN_SOURCE    /* ALWAYS BEFORE the include statement */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <limits.h>

//to compile: mpicc -std=c99 -Wall MPI_blank_template.c -o MPI_blank
//to run (simple): mpirun ./MPI_blank


// change only on pointer
void randomize_vector_p(double *vec, int size){
  int index;
  for (index= 0; index< size; index++ ) {
   vec[index] = drand48();
  }
}

int main(int argc, char *argv[]){


	int        comm_sz;               /* Number of processes    */
	int        my_rank;               /* My process rank        */
	//Don't put any MPI stuff before this line
	MPI_Init(&argc, &argv);  //sets up the MPI. Always this line!


	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    if( argc == 2 ){
	    // do some stuff
        srand48(time(NULL));
        int size = atoi(argv[1]);

        

        int for_each_process = (int) size/(comm_sz-1);
	    int remainder = size % (comm_sz-1);

        int my_first_i;
	    int my_last_i;

        int m = 0;

    if (my_rank != 0){
        if (my_rank-1 < remainder){
		    my_first_i = (my_rank-1)*(for_each_process+1);
		    my_last_i = my_first_i+for_each_process+1;
	}
	    else{
		    my_first_i = remainder*(for_each_process+1)+((my_rank-1)-remainder)*for_each_process;
		    my_last_i = my_first_i+for_each_process;
	}
    }
        double local_result;
	   if (my_rank != 0) {


            double * vector1 =  calloc(size,sizeof(double));
            double * vector2 =  calloc(size,sizeof(double));

           MPI_Recv(vector1,size,MPI_DOUBLE,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
           MPI_Recv(vector2,size,MPI_DOUBLE,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
           int i;

            for(i = my_first_i; i< my_last_i;i++){
                m++;
                double one = vector1[i];
                double two = vector2[i];
                local_result+=one * two;

	        }
           
           MPI_Send(&local_result,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	}
	    else
	{
		int q;
		double othersum;

		double globalsum = local_result;
        double * vector1 =  calloc(size,sizeof(double));
        double * vector2 =  calloc(size,sizeof(double));
        clock_t startTime = clock();

        randomize_vector_p(vector1, size);
        randomize_vector_p(vector2, size);

        int i;
        for(i = 0; i < size; i++){
            printf("should multiply %f, %f\n",vector1[i],vector2[i]);
        }



		for (q = 1; q < comm_sz; q++)
		{
            // printf("v1 = %f, v2 = %f\n",*vector1,*vector2);
            MPI_Send(vector1,size,MPI_DOUBLE,q,0,MPI_COMM_WORLD);
            MPI_Send(vector2,size,MPI_DOUBLE,q,1,MPI_COMM_WORLD);
			MPI_Recv(&othersum,1,MPI_DOUBLE,q,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

			globalsum += othersum;
		}

		printf("the total sum is %f\n", globalsum);
        clock_t endTime = clock();
        double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
        printf("That took %f ms\n",elapsed);

	}

    }
    else{
        printf("Too many arguments supplied or no argument given.\n");
    }


	MPI_Finalize();
	//please no MPI stuff after this line
	return 0;
}



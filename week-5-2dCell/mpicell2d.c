#include <stdio.h>
#include <time.h>
#include <string.h>
#include "2DCellAut.h"
#include "mpi.h"
#include <time.h>
#include <limits.h>
#include <math.h>
/* mpicell2d.c
 author: Yiran Zhang
*/
// Note:
// You can try compile and run command line "mpirun -np 2 ./mpicell 50 40",
// which means the 50 bits, 40 operations. If you only lack any of those 
// parameters, the code would assume you have 128 bits, 100 operations. 
// If you only offers one or two parameters, it assume you only wanna customize the bits
// number or both the bits number and operation number.



// We need to get values from our neighbors, and send values to our neighbors
// how to do it without deadlock?
// MPI_Send is non-blocking, except when it isn't
//
// When this function returns,
// leftval should contain the value sent by your left neighbor
// and rightval should contain the value sent by your right neighbor

void DistributeUpperAndLowerVals(int myID, int numprocs, char *mylocalcells, int localsize, int size, char *upperpad, char *lowerpad)
{
  int upperi;
  int loweri;
  if (myID == 0){
    upperi = numprocs-1;
    loweri = myID+1;
  }
  else if (myID == numprocs-1){
    upperi = myID-1;
    loweri = 0;
  }
  else{
    upperi = myID -1;
    loweri = myID+1;
  }

  char *sendupper = calloc(size,sizeof(char));
  char *sendlower = calloc(size,sizeof(char));


  memcpy(sendupper, &mylocalcells[0], size*sizeof(*mylocalcells));
  memcpy(sendlower, &mylocalcells[localsize*size-size], size*sizeof(*mylocalcells));

  //send upper and lower
  MPI_Send(sendupper,size,MPI_CHAR,upperi,0,MPI_COMM_WORLD);
  MPI_Send(sendlower,size,MPI_CHAR,loweri,0,MPI_COMM_WORLD);

  // receive upper and lower
  MPI_Recv(upperpad,size,MPI_CHAR,upperi,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  MPI_Recv(lowerpad,size,MPI_CHAR,loweri,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

}

void MPIRunCellWorld(int myID, int numprocs, char *localcells, int localsize, int size, int iterations, char * rule)
{
   char *upper = calloc(size,sizeof(char));
   char *lower = calloc(size,sizeof(char));
   int row = localsize +2;
   char *newcells = Make2DCellWorld(row, size);

  int itercount = 0;
  // printf("in core %d\n", myID);
  for (itercount = 0; itercount < iterations; itercount++)
     {
      // after calling this
      // the variables leftval and rightval
      // should have the values from the neighboring worlds.
       DistributeUpperAndLowerVals(myID, numprocs, localcells, localsize, size, upper, lower);
       memcpy(&newcells[0], upper, size*sizeof(*newcells));
       memcpy(&newcells[size], localcells, localsize*size*sizeof(*newcells));
       memcpy(&newcells[size + localsize*size], lower, size*sizeof(*newcells));
       int locali = 0;
       for (int locali = 1; locali < row-1 ; locali++){
         for (int localj = 0; localj < size ; localj++)
            Apply2DRuleAtLoc(newcells,localcells,locali*size+localj,row,size,rule);
        }

    }
    // print2DWorld(localcells,localsize,size,myID);
    free(newcells);

}

int main(int argc, char *argv[])
{
  //command line arguments are passed in as an array of strings!
  //where argc says how many arguments there are
  //(note the executable itself is the first argument, so argc is always 1)
   int i;
   int id;               /* Process rank */
   int p;                /* Number of processes */

   MPI_Init (&argc, &argv);
   MPI_Comm_rank (MPI_COMM_WORLD, &id);
   MPI_Comm_size (MPI_COMM_WORLD, &p);
   int WORLDSIZE;
   int maxiters;
   
   if (argc == 3){
    //  printf("herherherhehrehrherherherh");
     WORLDSIZE = atoi(argv[1]);
     maxiters = atoi(argv[2]);
   }
   else if (argc == 2){
     WORLDSIZE = atoi(argv[1]);
     maxiters = 10;
   }
   else{
     WORLDSIZE = 12;
     maxiters = 10;
   }

   srand48(time(NULL));
	 clock_t startTime = clock();

    // here need to generate localsize*
   if (WORLDSIZE%p != 0)
     {
       printf("Worldsize must be divisible by processors!");
       MPI_Finalize();
       exit(1);
     }

  char *localcells; //local array
   int localsize = (WORLDSIZE/p); //how many items you care about
   int paddedcols = WORLDSIZE+2;
   int paddedrows = localsize + 2;  //a
   int paddedsize = paddedcols*paddedrows;        

   if ((localcells = calloc(paddedsize,sizeof(char))) == NULL) {
	     printf("Memory allocation error!");
	     MPI_Finalize();
	     exit(1);
   }


  // localcells = malloc(localsize*WORLDSIZE,sizeof(int));
  Init2DCellWorld(localcells,localsize,WORLDSIZE);
  char *ruleset = calloc(RULESETSIZE,sizeof(char));
    if (id == 0) {
        ruleset = MakeRandomRuleSet();
    }
  MPI_Bcast(ruleset, RULESETSIZE, MPI_CHAR, 0, MPI_COMM_WORLD);

  //now everyone has their own slice of the world!

   printf("I am node %d, my local world is now:\n",id);
   print2DWorld(localcells,localsize,WORLDSIZE,id);

   int iterstep = 1;
   int curiters;
   char * global = Make2DCellWorld(WORLDSIZE, WORLDSIZE);

   for (curiters = 0; curiters < maxiters; curiters++)
     {
       //every node runs MPIRunCellWorld over its local world
       // notice that the local world is of size paddedsize
       // to accomodate the values recieved from Left and Right neigbhors
       //and make the running of the cell rules simpler.
       MPIRunCellWorld(id,p,localcells,localsize, WORLDSIZE, iterstep, ruleset);
       //     printf("I am node %d, my local world is now:\n",id);
      //  printWorld(localcells,localsize,id);
       MPI_Gather(localcells,localsize*WORLDSIZE,MPI_CHAR,global,localsize*WORLDSIZE,MPI_CHAR,0,MPI_COMM_WORLD);

            if (id == 0)
            {
                print2DWorld(global, WORLDSIZE, WORLDSIZE, id);
            }
        }

     
    
     if (id == 0){
      clock_t endTime = clock();
      double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
      printf("That took %f ms\n",elapsed);
     }

   MPI_Finalize();
}

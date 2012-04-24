// Zack Tillotson

#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SEARCH_DEPTH 10

using namespace std;

struct node {
	double eValue;
	int actionPath[MAX_SEARCH_DEPTH];
}

int main (int argc, char *argv[])
{

	// Setup ////////////////////////////////////////

	if(argc < 1) {
		cout << "Must enter search depth" << endl;
		exit(1);
	}

	int searchDepth = atoi(argv[1]);

	if(searchDepth > MAX_SEARCH_DEPTH) {
		cout << "Search depth must be less than " << MAX_SEARCH_DEPTH << endl;
		exit(1);
	}

	double elapsed_time, total_elapsed_time;
	int id, p, n;

	MPI_Init (&argc, &argv);
	MPI_Barrier(MPI_COMM_WORLD);
	elapsed_time = -MPI_Wtime();
	MPI_Comm_rank (MPI_COMM_WORLD, &id);
	MPI_Comm_size (MPI_COMM_WORLD, &p);

	// Setup complete ///////////////////////////////

	// Algorithm ////////////////////////////////////
	//
	// For some number of loops
	// 	Create price model for t = 1 to T + 1 days
	//	Broadcast price model
	//	Initialize solution arrays
	//	While t > 1
	//		Send and recieve data needed from neighbors for this round
	//		Calculate value of each position given value for next day's possible positions
	//		t++
	//	If head node, print results of valuation
	// Statistically summarize results

	for(int m = 0 ; m < maxRuns ; m++) {

		// Create price model
		double bPrices[searchDepth];

		if(id == 0) { 
			for(int i = 0 ; i < searchDepth; i++) {
				bPrices[i] = i * 1.; // TODO Do this more interestingly
			}

		}

		MPI_Bcast(bPrices, searchDepth, MPI_DOUBLE, 0, MPI_WORLD);

		

	}
	
	// Algorithm Done ///////////////////////////////

	// Finalize ////////////////////////////////////////
	elapsed_time += MPI_Wtime();
	MPI_Reduce (&elapsed_time, &total_elapsed_time, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); 

	if (!id) {
		printf ("Total computation time: %10.6f\n", total_elapsed_time);
		printf ("Total elapsed time: %10.6f\n", elapsed_time);
	}
	MPI_Finalize ();

	// Finalize Done ///////////////////////////////////

	return 0;

}

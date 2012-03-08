#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 100000

using namespace std;

int main (int argc, char *argv[])
{

	double elapsed_time, total_elapsed_time;
	int id, p, n;

	int low_value, high_value, size, proc0_size;
	int* ary;
	int i;

	MPI_Init (&argc, &argv);
	MPI_Barrier(MPI_COMM_WORLD);
	elapsed_time = -MPI_Wtime();
	MPI_Comm_rank (MPI_COMM_WORLD, &id);
	MPI_Comm_size (MPI_COMM_WORLD, &p);

	ary = (int *) malloc (ARRAY_SIZE);
	if (ary == NULL) {
		printf ("Cannot allocate enough memory\n");
		MPI_Finalize();
		exit (1);
	}

	if(id == 0) {
		fill_n(ary, 0, ARRAY_SIZE);
	}

	// Broadcast
	MPI_Bcast(ary, ARRAY_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

	// We're done, so post the execution times
	elapsed_time += MPI_Wtime();
	MPI_Reduce (&elapsed_time, &total_elapsed_time, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); 

	if (!id) {
		printf ("Total computation time: %10.6f\n", total_elapsed_time);
		printf ("Total elapsed time: %10.6f\n", elapsed_time);
	}
	MPI_Finalize ();
	return 0;

}

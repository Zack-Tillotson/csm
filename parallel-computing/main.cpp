#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {

	int id;
	int p;
	double elapsedTime;

	//long maxNumber = 100000000000;
	long maxNumber = 100000000;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	MPI_Barrier(MPI_COMM_WORLD);

	elapsedTime = -1 * MPI_Wtime();

	double localSum = 0;
	for(long i = id ; i < maxNumber ; i += p) {
		localSum += 1. / maxNumber * 4 / (1 + ((i + 0.5) / maxNumber) * ((i + 0.5) / maxNumber));
	}

	double globalSum;
	MPI_Reduce(&localSum, &globalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	elapsedTime += MPI_Wtime();
	double globalElapsedTime;
	MPI_Reduce(&elapsedTime, &globalElapsedTime, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if(id == 0) {
		printf("Elapsed Time = %f (Aggregate Time Taken: %f)\n", elapsedTime, globalElapsedTime);
		printf("Global sum = %f\n", globalSum);
	}

	printf("Process %d of %d is done\n", id, p);
	fflush(stdout);

	MPI_Finalize();

	return 0;

}

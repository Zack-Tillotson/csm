#include <mpi.h>
#include <stdio.h>

int check_circuit(int, int);

int main(int argc, char** argv) {

	int i;
	int id;
	int p;
	double elapsedTime;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	MPI_Barrier(MPI_COMM_WORLD);

	elapsedTime = -1 * MPI_Wtime();

	int localNumPassed = 0;
	for(long i = id ; i < 65536 ; i += p) {
		localNumPassed += check_circuit(id, i);	
	}

	int globalNumPassed;
	MPI_Reduce(&localNumPassed, &globalNumPassed, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	elapsedTime += MPI_Wtime();
	double globalElapsedTime;
	MPI_Reduce(&elapsedTime, &globalElapsedTime, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if(id == 0) {
		printf("Elapsed Time = %f (Aggregate Time Taken: %f)\n", elapsedTime, globalElapsedTime);
		printf("Global inputs passed (of 65536)= %d\n", globalNumPassed);
	}

	printf("Process %d of %d is done\n", id, p);
	fflush(stdout);

	MPI_Finalize();

	return 0;

}

/* Return 1 if 'i'th bit of 'n' is 1; 0 otherwise */
#define EXTRACT_BIT(n,i) ((n&(1<<i))?1:0)

int check_circuit (int id, int z) {

	int v[16];        /* Each element is a bit of z */
	int i;

	for (i = 0; i < 16; i++) v[i] = EXTRACT_BIT(z,i);

	if ((v[0] || v[1]) && (!v[1] || !v[3]) && (v[2] || v[3]) && (!v[3] || !v[4]) && (v[4] || !v[5]) && (v[5] || !v[6]) && (v[5] || v[6])
		&& (v[6] || !v[15]) && (v[7] || !v[8])
		&& (!v[7] || !v[13]) && (v[8] || v[9])
		&& (v[8] || !v[9]) && (!v[9] || !v[10])
		&& (v[9] || v[11]) && (v[10] || v[11])
		&& (v[12] || v[13]) && (v[13] || !v[14])
		&& (v[14] || v[15])) {
			printf ("%d) %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n", id,
				 v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],
				 v[10],v[11],v[12],v[13],v[14],v[15]);
			fflush (stdout);
			return 1;
	} else {
		return 0;
	}

}

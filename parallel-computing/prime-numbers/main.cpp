#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b)  ((a)<(b)?(a):(b))
#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) ( BLOCK_LOW((id)+1,p,n)-1 ) 
#define BLOCK_SIZE(id,p,n) (BLOCK_LOW( (id)+1, p, n) - BLOCK_LOW( (id), p, n  ) )
#define BLOCK_OWNER(index,p,n) ( ( ((p)*(index)+1)-1 ) / (n) )

using namespace std;

int getMarkedSize(int size); 
void setMarkedValue(char* marked, int startsOdd, int index, int value);
int getMarkedValue(char* marked, int startsOdd, int index);

int main (int argc, char *argv[])
{

	double elapsed_time;
	int id, p, n;

	int low_value, high_value, size, proc0_size;
	char* marked;
	int i, index, prime, first, count, global_count;
	int startsOdd;

	MPI_Init (&argc, &argv);
	MPI_Barrier(MPI_COMM_WORLD);
	elapsed_time = -MPI_Wtime();
	MPI_Comm_rank (MPI_COMM_WORLD, &id);
	MPI_Comm_size (MPI_COMM_WORLD, &p);

	if (argc != 2) {
		if (!id) printf ("Command line: %s <m>\n", argv[0]);
		MPI_Finalize(); exit (1);
	}

	n = atoi(argv[1]);
	low_value = 2 + BLOCK_LOW(id,p,n-1);
	high_value = 2 + BLOCK_HIGH(id,p,n-1);
	size = BLOCK_SIZE(id,p,n-1);
	proc0_size = (n-1)/p;
	startsOdd = low_value % 2;

	if ((2 + proc0_size) < (int) sqrt((double) n)) {
		if (!id) printf ("Too many processes\n");
		MPI_Finalize();
		exit (1);
	}

	marked = (char *) malloc (getMarkedSize(size));
	if (marked == NULL) {
		printf ("Cannot allocate enough memory\n");
		MPI_Finalize();
		exit (1);
	}

	for (i = 0; i < size; i++) setMarkedValue(marked, startsOdd, i, 0);

	if (!id) index = 0;
	prime = 3;
	do {

		if (prime * prime > low_value)
			first = prime * prime - low_value;
		else {
			if (!(low_value % prime)) first = 0;
			else first = prime - (low_value % prime);
		}
		for (i = first; i < size; i += prime) setMarkedValue(marked, startsOdd, i, 1);
	
		// Each program will naively look through all odd numbers, instead of using 
		// broadcasts to coordinate through the primes of the base process.
		prime+=2;

	} while (prime * prime <= n);

	count = 0; 
	for (i = 0; i < size; i++)
		if (!getMarkedValue(marked, startsOdd, i)) count++;
	MPI_Reduce (&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 
	elapsed_time += MPI_Wtime();

	global_count++; // Since we aren't counting 2
	
	if (!id) {
		printf ("%d primes are less than or equal to %d\n", global_count, n);
		printf ("Total elapsed time: %10.6f\n", elapsed_time);
	}
	MPI_Finalize ();
	return 0;

}

int getMarkedSize(int size) {
	return (size + 1) / 2;
}

void setMarkedValue(char* marked, int startsOdd, int index, int value) {
	if((startsOdd == 0 && index % 2) || (startsOdd == 1 && index % 2 == 0)) {
		marked[(index + 1) / 2] = value;
	}
}

int getMarkedValue(char* marked, int startsOdd, int index) {
	if((!startsOdd && index % 2) || (startsOdd && index % 2 == 0)) {
		return marked[(index + 1) / 2];
	} else {
		return 1;
	}
}

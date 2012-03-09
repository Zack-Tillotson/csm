#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 100000000

using namespace std;

bool haveReceiver(int id, int r, int n, int p);
int sizeOfPiece(int sizeOfArray, int n);
int indexOfPieceToSend(int id, int r);
bool haveSender(int id, int r, int n, int p);
void sendPiece(int* ary, int i, int s, int id);
void receivePiece(int* ary, int i, int s, int id);

int main (int argc, char *argv[])
{

	double elapsed_time, total_elapsed_time;
	int id, p;

	int* ary;

	MPI_Init (&argc, &argv);
	MPI_Barrier(MPI_COMM_WORLD);
	elapsed_time = -MPI_Wtime();
	MPI_Comm_rank (MPI_COMM_WORLD, &id);
	MPI_Comm_size (MPI_COMM_WORLD, &p);

	ary = new int[ARRAY_SIZE];
	if (ary == NULL) {
		printf ("Cannot allocate enough memory\n");
		MPI_Finalize();
		exit (1);
	}

	if(id == 0) {
		fill_n(ary, 0, ARRAY_SIZE);
	}

	// Pipeline Broadcast ////

	// Number of pieces to break message into
	int n = p - 1; 

	for(int r = 1 ; r <= p + n - 2 ; r++) { // Number of steps needed to send piece is (p - 1) + (n - 1)
	
		// Evens and odds go different directions so we don't get deadlock	
		if(id % 2 == 0 || 1) {

			if(haveReceiver(id, r, n, p)) {
				sendPiece(ary, sizeOfPiece(ARRAY_SIZE, n) * indexOfPieceToSend(id, r), sizeOfPiece(ARRAY_SIZE, n), id + 1);
			}
			if(haveSender(id, r, n, p)) {
				receivePiece(ary, sizeOfPiece(ARRAY_SIZE, n) * indexOfPieceToSend(id - 1, r), sizeOfPiece(ARRAY_SIZE, n), id - 1);
			}

		} else {

			if(haveSender(id, r, n, p)) {
				receivePiece(ary, sizeOfPiece(ARRAY_SIZE, n) * indexOfPieceToSend(id - 1, r), sizeOfPiece(ARRAY_SIZE, n), id - 1);
			}
			if(haveReceiver(id, r, n, p)) {
				sendPiece(ary, sizeOfPiece(ARRAY_SIZE, n) * indexOfPieceToSend(id, r), sizeOfPiece(ARRAY_SIZE, n), id + 1);
			}

		}

	}

	delete[] ary;

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

// This is the optimal size of each piece we are sending
int sizeOfPiece(int sizeOfArray, int n) {
	return ceil((1. * sizeOfArray ) / n);
}

// This is just the index of the piece to send, if it's 0 to n then it's legit
int indexOfPieceToSend(int id, int r) {
	return r - 1 - id;
}

bool haveReceiver(int id, int r, int n, int p) {
//printf("Does #%d in round %d have a receiver for piece %d of %d? \n", id, r, indexOfPieceToSend(id, r), n);
	return indexOfPieceToSend(id, r) >= 0 && indexOfPieceToSend(id, r) < n && id < p - 1;
}

// Will get sent to if the process below it is sending
bool haveSender(int id, int r, int n, int p) {
	return haveReceiver(id - 1, r, n, p) && id > 0;
}

void sendPiece(int* ary, int i, int s, int id) {
	int* local_ary = new int[s];
	for(int x = 0 ; x < s && i + x < ARRAY_SIZE ; x++) {
		local_ary[x] = ary[i + x];
	}
	MPI_Send(local_ary, s, MPI_INT, id, 0, MPI_COMM_WORLD);
	delete[] local_ary;
}
void receivePiece(int* ary, int i, int s, int id) {
	int* local_ary = new int[s];
	MPI_Status status;
	MPI_Recv(local_ary, s, MPI_INT, id, 0, MPI_COMM_WORLD, &status);
	for(int x = 0 ; x < s && i + x - 1 < ARRAY_SIZE ; x++) {
		ary[i + x] = local_ary[x];
	}
	delete[] local_ary;
}

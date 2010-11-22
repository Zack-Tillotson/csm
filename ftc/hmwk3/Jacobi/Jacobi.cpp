#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "mpi.h"
#include <math.h>

using namespace std;

#define NAME_LEN 	40
#define MAX_M 		100

#define N 		120		// Size of this chunk of matrix to compute
#define M 		120

int main( int argc, char** argv ) {

	// See if it's a restart
	bool isRestart = argc == 2 && strcmp(argv[1], "-r") == 0;

	int rank, size, len;				// MPI attributes
	char processor_name[MPI_MAX_PROCESSOR_NAME];	// Processor name
	int i;						// Iteration number
	double c_vals [N+2][M];				// Current value matrix
	double n_vals [N][M];				// New value matrix

	MPI_Init( &argc, &argv );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Get_processor_name(processor_name,&len);

	if(!isRestart && argc == 1) { 			// Normal running, init for new run

		i = 0;

		for(int r = 0 ; r < M ; r++)		// Bottom ghost edge is prior rank
			c_vals[0][r] = rank - 1;
		for(int t = 1 ; t < N + 1 ; t++)
			for(int r = 0 ; r < M ; r++)
				c_vals[t][r] = rank;
		for(int r = 0 ; r < M ; r++)		// Top ghost edge is next rank
			c_vals[N + 1][r] = rank + 1;

		if(rank == 0)				// Bottom-most row is -1
			for(int r = 0 ; r < M ; r++)
				c_vals[1][r] = -1;

		if(rank == size - 1)			// Top-most row is -1
			for(int r = 0 ; r < M ; r++)
				c_vals[N][r] = -1;
			

	} else if(isRestart) { 				// Load from backup 

		char numString[NAME_LEN];
		sprintf(numString, "jacobi.%d.bup", rank);
		
		string line;
		ifstream myfile (numString);;
		if (myfile.is_open()) {
			if (myfile.good()) {
				myfile >> i;
				for(int a = 0 ; a < N + 2 ; a++)
					for(int b = 0 ; b < M ; b++)
						myfile >> c_vals[a][b];
			}
			myfile.close();
		}

	} else { 					// Wrong usage
		cerr << "Bad usage" << endl;
		exit(1);
	}

	double totDiffnorm = 1000000;
	for (i; i < 100 && totDiffnorm > .01; i++) {

		// Update values and calculate the local convergence amount
		for(int t = 1 ; t < N + 1 ; t++)
			for(int r = 0 ; r < M ; r++)
				n_vals[t-1][r] = (c_vals[t-1][r] + c_vals[t+1][r] + c_vals[t][r-1] + c_vals[t][r+1]) / 4;

		double diffnorm = 0;
		for(int t = 1 ; t < N + 1 ; t++) {
			if(rank == 0 && t == 1) continue; 		// Don't update the top-most and bottom-most edges
			if(rank == size - 1 && t == N) continue;
			for(int r = 0 ; r < M ; r++) {
				diffnorm += (c_vals[t][r] - n_vals[t-1][r])*(c_vals[t][r] - n_vals[t-1][r]);
				c_vals[t][r] = n_vals[t-1][r]; 
			}
		}

		// Send ghost vars up - even send first, odd recv first
		if(rank % 2 == 0) {

			if(rank != size -1) 	MPI_Send(c_vals[N], M, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD);
			if(rank != 0) 		MPI_Recv(c_vals[N], M, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, NULL);
		
		} else {

			if(rank != 0) 		MPI_Recv(c_vals[N], M, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, NULL);
			if(rank != size -1) 	MPI_Send(c_vals[N], M, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD);

		}

		// Send ghost vars down - even send first, odd recv first
		if(rank % 2 == 0) {

			if(rank != 0) 		MPI_Send(c_vals[1], M, MPI_DOUBLE, rank - 1, NULL, MPI_COMM_WORLD);
			if(rank != size - 1)	MPI_Recv(c_vals[1], M, MPI_DOUBLE, rank + 1, NULL, MPI_COMM_WORLD, NULL);
		
		} else {

			if(rank != size - 1)	MPI_Recv(c_vals[1], M, MPI_DOUBLE, rank + 1, NULL, MPI_COMM_WORLD, NULL);
			if(rank != 0) 		MPI_Send(c_vals[1], M, MPI_DOUBLE, rank - 1, NULL, MPI_COMM_WORLD);

		}

		// Send convergence of local matrix
		MPI_Reduce(&diffnorm, &totDiffnorm, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		totDiffnorm = sqrt(totDiffnorm);

		// Print current convergence
		if(rank == 0) {
			fprintf(stdout, "[Iteration: %d][Convergence: %f]\n", i, totDiffnorm);
		}

		MPI_Barrier(MPI_COMM_WORLD);

		// Checkpoint every 20 iterations
		if(i % 20 == 0 || true) {

			char numString[NAME_LEN];
			sprintf(numString, "jacobi.%d.bup", rank);

			ofstream myfile;
			myfile.open (numString);
			myfile << i << endl;
			for(int a = 0 ; a < N + 2 ; a++)
				for(int b = 0 ; b < M ; b++)
					myfile << c_vals[a][b] << endl;
			myfile.close();

		}

		// Simulate a failure in iteration 80
		if(!isRestart && i == 79)  {
			exit(1);
		}

	}

	MPI_Finalize();

	return 0;

}

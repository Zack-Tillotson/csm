#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "mpi.h"

using namespace std;

const int NAME_LEN = 40;
const int MAX_M = 100;

int main( int argc, char** argv ) {

	// See if it's a restart
	bool isRestart = argc == 2 && strcmp(argv[1], "-r") == 0;

	int rank, size, len;				// MPI attributes
	char processor_name[MPI_MAX_PROCESSOR_NAME];	// Processor name
	int i;						// Iteration number
	int tot_n, tot_m;				// Total size of the matrix to compute
	int n, m;					// Size of this chunk of matrix to compute
	double** c_vals;				// Current value matrix
	double** n_vals;				// New value matrix

	MPI_Init( &argc, &argv );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Get_processor_name(processor_name,&len);

	if(!isRestart && argc == 3) { 			// Normal running, init for new run

		i = 0;

		tot_n = (int) strtoul(argv[1], 0, 0);
		tot_m = (int) strtoul(argv[2], 0, 0);

		n = tot_n / size;
		m = tot_m;

		c_vals = new double*[n + 2];		// n+2 x m array
		for(int t = 0 ; t < n + 2 ; t++)
			c_vals[t] = new double[m];

		for(int r = 0 ; r < m ; r++)		// Bottom ghost edge is prior rank
			c_vals[0][r] = rank - 1;
		for(int t = 1 ; t < n + 1 ; t++)
			for(int r = 0 ; r < m ; r++)
				c_vals[t][r] = rank;
		for(int r = 0 ; r < m ; r++)		// Top ghost edge is next rank
			c_vals[n + 1][r] = rank + 1;

		if(rank == 0)				// Bottom-most row is -1
			for(int r = 0 ; r < m ; r++)
				c_vals[1][r] = -1;

		if(rank == size - 1)			// Top-most row is -1
			for(int r = 0 ; r < m ; r++)
				c_vals[n][r] = -1;
			

		n_vals = new double*[n];
		for(int t = 0 ; t < n ; t++)
			n_vals[t] = new double[m];

	} else if(isRestart) { 				// Load from backup 
	} else { 					// Wrong usage
		exit(1);
	}


	for (i;i<100;i++) {

		// Update values
		for(int t = 1 ; t < n + 1 ; t++)
			for(int r = 0 ; r < m ; r++)
				n_vals[t-1][r] = (c_vals[t-1][r] + c_vals[t+1][r] + c_vals[t][r-1] + c_vals[t][r+1]) / 4;

		for(int t = 1 ; t < n + 1 ; t++) {
			if(rank == 0 && t == 1) continue; 		// Don't update the top-most and bottom-most edges
			if(rank == size - 1 && t == n) continue;
			for(int r = 0 ; r < m ; r++)
				c_vals[t-1][r] = n_vals[t][r]; 
		}

		// Send ghost vars down - even send first, odd recv first
		// Send ghost vars up - even send first, odd recv first

		// Send convergence of local matrix

		// Print current convergence
		if(rank == 0) {

			fprintf(stderr, "Iteration %d: Hello world from process %d (processor: %s) of %d\n", i, rank, processor_name, size );

		}

		MPI_Barrier(MPI_COMM_WORLD);

		// Checkpoint every 20 iterations
		if(i % 20 == 0) {

			string fileName("jacobi.");
			fileName += rank;//+ ".bup";
			fileName += ".bup";

			ofstream myfile;
			myfile.open (fileName.c_str());
			myfile << i << endl;
			myfile << n << " " << m << endl;
			for(int a = 0 ; a < n + 2 ; a++)
				for(int b = 0 ; b < m ; b++)
					myfile << c_vals[a][b] << " " << endl;
			myfile.close();

		}

		// Simulate a failure in iteration 80
		if(!isRestart && i == 79) {
			//exit(1);
		}

	}

	MPI_Finalize();

	// TODO Delete mems

	return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "mpi.h"

using namespace std;

int main( int argc, char** argv ) {

	// Any args pass to the prog mean it's a restart
	bool isRestart = argc > 1;

	int rank, size, len, i;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	// Initialize from backup file if this is a restart, otherwise start at the beginning
	if(isRestart) {

		string line;
		ifstream myfile ("HelloWorld.bup");
		if (myfile.is_open()) {
			if (myfile.good()) {
				myfile >> i;
			}
			myfile.close();
		}

	} else { 
		i = 0;
	}

	MPI_Init( &argc, &argv );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Get_processor_name(processor_name,&len);

	for (i;i<100;i++) {

		fprintf(stderr, "Iteration %d: Hello world from process %d (processor: %s) of %d\n", i, rank, processor_name, size );

		MPI_Barrier(MPI_COMM_WORLD);

		// Checkpoint every 20 iterations
		if(i % 20 == 0 && rank == 0) {

			  ofstream myfile;
			  myfile.open ("HelloWorld.bup");
			  myfile << i;
			  myfile.close();

		}

		// Simulate a failure in iteration 80
		if(!isRestart && i == 79) {
			exit(1);
		}

	}

	MPI_Finalize();

	return 0;

}

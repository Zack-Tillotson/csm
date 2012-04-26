// Zack Tillotson

#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SEARCH_DEPTH 10
#define MIN_VBUCKET_NUM 1 
#define PENALTY_VALUE -100000.

using namespace std;

struct Node {
	double eValue;
	int actionPath[MAX_SEARCH_DEPTH];
};

void usage() {
	cout << "Usage: $prog <search depth, int> <number of volume buckets, int> <initial volume bucket, 0 base int> <number of run iterations, int>" << endl;
	exit(1);
}

void addToMaxNode(Node* cNode, Node* hNodes, int i, int maxI, int offset, int t) {

	int index = i + offset;
	int bestA = 0;

	for(int a = -1 * offset ; a <= offset ; a++) {
		if(hNodes[i + a + offset].eValue > hNodes[index].eValue) {
			index = i + a + offset;
			bestA = a;
		}
	}

	cNode->eValue += hNodes[index].eValue;
	cNode->actionPath[t] = bestA;

}
				
void copyNode(Node* to, Node* from, int t) {

	to->eValue = from->eValue;
	for(int i = 0 ; i < t + 1 ; i++) {
		to->actionPath[i] = from->actionPath[i];
	}	

}

void exchangeWithNeighbors(Node* hNode, int width, int offset, int o, int id, int t, int p) {

	if(id % 2 == 0) {
		
		if(id + 1 < p) {
			//printf("%d sending right\n", id);
			MPI_Send(&(hNode[offset + width - 1 - (offset - 1 - o)].eValue), 1, MPI_DOUBLE, id + 1, 0, MPI_COMM_WORLD);
			MPI_Send(hNode[offset + width - 1 - (offset - 1 - o)].actionPath, MAX_SEARCH_DEPTH, MPI_INT, id + 1, 0, MPI_COMM_WORLD);
			//printf("%d recving right\n", id);
			MPI_Recv(&(hNode[offset + width + o].eValue), 1, MPI_DOUBLE, id + 1, 0, MPI_COMM_WORLD, 0);
			MPI_Recv(hNode[offset + width + o].actionPath, MAX_SEARCH_DEPTH, MPI_INT, id + 1, 0, MPI_COMM_WORLD, 0);
		}

		if(id > 0) {
			//printf("%d sending left\n", id);
			MPI_Send(&(hNode[offset + o].eValue), 1, MPI_DOUBLE, id - 1, 0, MPI_COMM_WORLD);
			MPI_Send(hNode[offset + o].actionPath, MAX_SEARCH_DEPTH, MPI_INT, id - 1, 0, MPI_COMM_WORLD);
			//printf("%d recving left\n", id);
			MPI_Recv(&(hNode[offset - 1 - o].eValue), 1, MPI_DOUBLE, id - 1, 0, MPI_COMM_WORLD, 0);
			MPI_Recv(hNode[offset - 1 - o].actionPath, MAX_SEARCH_DEPTH, MPI_INT, id - 1, 0, MPI_COMM_WORLD, 0);
		}

	} else {

		if(id > 0) {
			//printf("%d recving left\n", id);
			MPI_Recv(&(hNode[offset - 1 - o].eValue), 1, MPI_DOUBLE, id - 1, 0, MPI_COMM_WORLD, 0);
			MPI_Recv(hNode[offset - 1 - o].actionPath, MAX_SEARCH_DEPTH, MPI_INT, id - 1, 0, MPI_COMM_WORLD, 0);
			//printf("%d sending left\n", id);
			MPI_Send(&(hNode[offset + o].eValue), 1, MPI_DOUBLE, id - 1, 0, MPI_COMM_WORLD);
			MPI_Send(hNode[offset + o].actionPath, MAX_SEARCH_DEPTH, MPI_INT, id - 1, 0, MPI_COMM_WORLD);
		}

		if(id + 1 < p) {
			//printf("%d recving right\n", id);
			MPI_Recv(&(hNode[offset + width + o].eValue), 1, MPI_DOUBLE, id + 1, 0, MPI_COMM_WORLD, 0);
			MPI_Recv(hNode[offset + width + o].actionPath, MAX_SEARCH_DEPTH, MPI_INT, id + 1, 0, MPI_COMM_WORLD, 0);
			//printf("%d sending right\n", id);
			MPI_Send(&(hNode[offset + width - 1 - (offset - 1 - o)].eValue), 1, MPI_DOUBLE, id + 1, 0, MPI_COMM_WORLD);
			MPI_Send(hNode[offset + width - 1 - (offset - 1 - o)].actionPath, MAX_SEARCH_DEPTH, MPI_INT, id + 1, 0, MPI_COMM_WORLD);
		}

	}
	
}
				
int main (int argc, char *argv[])
{

	// Setup ////////////////////////////////////////

	if(argc < 5) {
		usage();
	}

	int searchDepth = atoi(argv[1]);
	int vBucketNum = atoi(argv[2]);
	int vBucketInit = atoi(argv[3]);
	int maxRuns = atoi(argv[4]);

	if(searchDepth > MAX_SEARCH_DEPTH) {
		cout << "Search depth must be less than " << MAX_SEARCH_DEPTH << endl;
		usage();
	}

	if(vBucketNum < MIN_VBUCKET_NUM) {
		cout << "Number of buckets must be greater than " << MIN_VBUCKET_NUM << endl;
		usage();
	}

	if(vBucketInit < 0 || vBucketInit > vBucketNum - 1) {
		cout << "Initial volume bucket must be between 0 and the number of volume buckets" << endl;
		usage();
	}

	if(maxRuns < 1) {
		cout << "Must run at least once" << endl;
		usage();
	}

	double elapsed_time, total_elapsed_time;
	int id, p, n;

	int offset;
	int globalWidth;
	int localStart;
	int localEnd;
	int width;


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

	offset = 1; // Number of volume moves per day (ex: 1 means from 0 to -1, 0, or 1)
	globalWidth = vBucketNum; // Number of volume buckets
	localStart = id * vBucketNum / p;
	localEnd = (id + 1) * vBucketNum / p;
	width = localEnd - localStart;

	printf("Offset: %i, gWidth: %i, lStart: %i, lEnd: %i, width: %i\n", offset, globalWidth, localStart, localEnd, width);

	for(int m = 0 ; m < maxRuns ; m++) {

		// Create price model
		double bPrices[searchDepth];

		if(id == 0) { 
			for(int i = 0 ; i < searchDepth; i++) {
				bPrices[i] = i * 1.; // TODO Do this more interestingly
			}

		}

		MPI_Bcast(bPrices, searchDepth, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		// Initialize data structures
		Node* cNode = new Node[width];
		Node* hNode = new Node[width + 2 * offset];

		// All end solutions are penalized based on how far from neutral the volume change has been
		for(int i = 0 ; i < width + 2 * offset; i++) {
			int dist = vBucketInit - localStart - i - offset;
			if(dist < 0) {
				dist *= -1;
			}
			hNode[i].eValue = PENALTY_VALUE * dist;
		}

		// While not at the current day yet
		for(int t = 0 ; t < searchDepth ; t++) {

			// Update each of the current nodes to include optimal next step
			for(int i = 0 ; i < width ; i++) {
				addToMaxNode(&cNode[i], hNode, i, width + 1, offset, t); 
			}

			// Copy current nodes we have to history
			for(int i = 0 ; i < width ; i++) {
				copyNode(&hNode[i + offset], &cNode[i], t);
			}

			// Copy current nodes from other processors to history
			for(int o = 0 ; o < offset; o++) {
				exchangeWithNeighbors(hNode, width, offset, o, id, t, p);	
			}

			// Just some output
			for(int y = offset ; y < width + offset; y++) {
				printf("Round %i, Node %i: eVal %f, actions ", t, y, hNode[y].eValue);
				for(int x = 0 ; x < t + 1; x++) {
					printf("%i, ", hNode[y].actionPath[x]);
				}
				printf("\n");
			}
			printf("\n");

		}

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

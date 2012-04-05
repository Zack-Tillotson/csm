// Zack Tillotson
// This program will run a series of matrix multiplications of increasing size.

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

void seedMatrixRandomly(double** m, int size);
void doMatrixMultiplication(double** a, double** b, double** c, int size);
 
main()
{

	double ** a, **b, **c;
	int s, i;
	long t;
	struct timeval start, end;

	for(s = 500; s <= 5000; s+= 500) {

		a = (double**)malloc(s * sizeof(double*));
		b = (double**)malloc(s * sizeof(double*));
		c = (double**)malloc(s * sizeof(double*));
		for (i = 0; i < s; i++) {
			a[i] = (double*)malloc(s * sizeof(double));
			b[i] = (double*)malloc(s * sizeof(double));
			c[i] = (double*)malloc(s * sizeof(double));
		}

		seedMatrixRandomly(a, s);
		seedMatrixRandomly(b, s);
		seedMatrixRandomly(c, s);

		printf("Starting multiplication [size %d]\n", s);
		gettimeofday(&start, NULL); 

		// Doing the multiplication //////
		doMatrixMultiplication(a, b, c, s);
		//////////////////////////////////

		gettimeofday(&end, NULL); 
		t = ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec)/1000.0) + 0.5;

		printf("Finished multiplication [time %d]\n\n", (int)t);

		for (i = 0; i < s; i++) {
			free(a[i]);
			free(b[i]);
			free(c[i]);
		}
		free(a);
		free(b);
		free(c);

	}

	return 0;

}

void seedMatrixRandomly(double** m, int size) {

	int i, j;
	for(i = 0 ; i < size ; i++) {
		for(j = 0 ; j < size ; j++) {
			m[i][j] = random() % 100 + 1;
		}
	}

}

void doMatrixMultiplication(double** a, double** b, double** c, int size) {

	
   

}
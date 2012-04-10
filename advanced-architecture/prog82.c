// Zack Tillotson
// This program will run a series of matrix multiplications of increasing size.

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

void seedMatrixRandomly(double* m, int size);
void doMatrixMultiplication(double* a, double* b, double* c, int size);
 
main()
{

	double * a, *b, *c, *savedC;
	int s, i;
	long t;
	struct timeval start, end;

	for(s = 500; s <= 5000; s+= 500) {

		a = (double*)malloc(s * s * sizeof(double));
		b = (double*)malloc(s * s * sizeof(double));
		c = (double*)malloc(s * s * sizeof(double));

                seedMatrixRandomly(a, s);
                seedMatrixRandomly(b, s);
                seedMatrixRandomly(c, s);

                printf("Starting multiplication [size %d]\n", s);
                gettimeofday(&start, NULL);

		// Doing the multiplication ////////////
                doMatrixMultiplication(a, b, c, s);
		////////////////////////////////////////

                gettimeofday(&end, NULL);
                t = ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec)/1000.0) + 0.5;

                printf("Finished multiplication [time %d], calculating difference\n", (int)t);

                savedC = c;
                c = (double*)malloc(s * s * sizeof(double));
                seedMatrixRandomly(c, s);

                // Calculating the verifiation solution //////
                char n = 'n';
                double scalar = 1.0;
                dgemm_(&n, &n, &s, &s, &s, &scalar, a, &s, b, &s, &scalar, c, &s);
                //////////////////////////////////////////////


                double totalOff = 0;
                for(i = 0 ; i < s * s; i++) {
                        totalOff += c[i] - savedC[i];
                }

                printf("Difference calculated [value %f]\n\n", totalOff);

                free(a);
                free(b);
                free(c);
                free(savedC);

	}

	return 0;

}

void seedMatrixRandomly(double* m, int size) {

	srand(0);

	int i, j;
	for(i = 0 ; i < size ; i++) {
		for(j = 0 ; j < size ; j++) {
			m[i * size + j] = random() % 100 + 1;
		}
	}

}

void doMatrixMultiplication(double* a, double* b, double* c, int size) {

	int i, j, k;
	int ii, jj, kk;

	int t = 33; // TODO Optimize

	for(j = 0 ; j < size ; j += t) {
		for(k = 0 ; k < size ; k += t) {                
			for(i = 0 ; i < size ; i += t) { 
				for(jj = j ; jj < size && jj < j + t ; jj++) {
					for(kk = k ; kk < size && kk < k + t ; kk++) {   
						for(ii = i ; ii < size && ii < i + t ; ii++) {  
                                                        c[ii * size + jj] = c[ii * size + jj] + a[ii * size + kk] * b[kk * size + jj];
                                                }
                                        }
                                }
                        }
                }
        }


}

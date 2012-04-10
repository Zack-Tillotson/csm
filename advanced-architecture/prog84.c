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


	int t = 33;
	int jj1, jj2, jj3, jj4, jj5, jj6, jj7, jj8;
	double save1, save2, save3, save4, save5, save6, save7, save8;

	for(i = 0 ; i < size ; i += t) {
                for(k = 0 ; k < size ; k += t) {
			for(j = 0 ; j < size ; j += t) { 
				for(ii = i ; ii < size && ii < i + t ; ii++) {
					for(jj = j ; jj + 7 < size && jj + 7 < j + t ; jj += 8) { 

						jj1 = jj + 0;
						jj2 = jj + 1;
						jj3 = jj + 2;
						jj4 = jj + 3;
						jj5 = jj + 4;
						jj6 = jj + 5;
						jj7 = jj + 6;
						jj8 = jj + 7;

						save1 = c[ii * size + jj1];
						save2 = c[ii * size + jj2];
						save3 = c[ii * size + jj3];
						save4 = c[ii * size + jj4];
						save5 = c[ii * size + jj5];
						save6 = c[ii * size + jj6];
						save7 = c[ii * size + jj7];
						save8 = c[ii * size + jj8];

						for(kk  = k ; kk < size && kk < k + t ; kk++) {
                                                        save1 = save1 + a[ii * size + kk] * b[kk * size + jj1];
                                                        save2 = save2 + a[ii * size + kk] * b[kk * size + jj2];
                                                        save3 = save3 + a[ii * size + kk] * b[kk * size + jj3];
                                                        save4 = save4 + a[ii * size + kk] * b[kk * size + jj4];
                                                        save5 = save5 + a[ii * size + kk] * b[kk * size + jj5];
                                                        save6 = save6 + a[ii * size + kk] * b[kk * size + jj6];
                                                        save7 = save7 + a[ii * size + kk] * b[kk * size + jj7];
                                                        save8 = save8 + a[ii * size + kk] * b[kk * size + jj8];
                                                }
						c[ii * size + jj1] = save1;
						c[ii * size + jj2] = save2;
						c[ii * size + jj3] = save3;
						c[ii * size + jj4] = save4;
						c[ii * size + jj5] = save5;
						c[ii * size + jj6] = save6;
						c[ii * size + jj7] = save7;
						c[ii * size + jj8] = save8;

                                        }

					// This cleans up the last few rows if needed
					for( ; jj < size && jj < j + t ; jj++) {  
						save1 = c[ii * size + jj];
						for(kk  = k ; kk < size && kk < k + t ; kk++) {
                                                        save1 = save1 + a[ii * size + kk] * b[kk * size + jj];
                                                }
						c[ii * size + jj] = save1;
					}
                                }
                        }
                }
        }

}

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
	int ii, jj;


	int t = 33;
	int ii1, ii2, ii3, ii4, ii5, ii6, ii7, ii8;
	int kk1, kk2, kk3, kk4, kk5, kk6, kk7, kk8;
	double save1, save2, save3, save4, save5, save6, save7, save8;

	for(j = 0 ; j < size ; j += t) { 
                for(k = 0 ; k < size ; k += t) {
                        for(i = 0 ; i < size ; i += t) {
                                for(jj = j ; jj < size && jj < j + t ; jj++) { 
					for(ii = i ; ii < size && ii < i + t ; ii+=8) {

						ii1 = ii + 0;
						ii2 = ii + 1;
						ii3 = ii + 2;
						ii4 = ii + 3;
						ii5 = ii + 4;
						ii6 = ii + 5;
						ii7 = ii + 6;
						ii8 = ii + 7;

						save1 = c[ii1 * size + jj];
						for(kk1  = k ; kk1 < size && kk1 < k + t ; kk1++) {
                                                        save1 = save1 + a[ii1 * size + kk1] * b[kk1 * size + jj];
                                                }
						c[ii1 * size + jj] = save1;

						if(ii2 < size && ii2 < i + t) {
							save2 = c[ii2 * size + jj];
							for(kk2 = k ; kk2 < size && kk2 < k + t ; kk2++) {
								save2 = save2 + a[ii2 * size + kk2] * b[kk2 * size + jj];
							}
							c[ii2 * size + jj] = save2;
						}

						if(ii3 < size && ii3 < i + t) {
							save3 = c[ii3 * size + jj];
							for(kk3 = k ; kk3 < size && kk3 < k + t ; kk3++) {
								save3 = save3 + a[ii3 * size + kk3] * b[kk3 * size + jj];
							}
							c[ii3 * size + jj] = save3;
						}

						if(ii4 < size && ii3 < i + t) {
							save4 = c[ii4 * size + jj];
							for(kk4 = k ; kk4 < size && kk4 < k + t ; kk4++) {
								save4 = save4 + a[ii4 * size + kk4] * b[kk4 * size + jj];
							}
							c[ii4 * size + jj] = save4;
                                                }

						if(ii5 < size && ii5 < i + t) {
							save5 = c[ii5 * size + jj];
							for(kk5 = k ; kk5 < size && kk5 < k + t ; kk5++) {
								save5 = save5 + a[ii5 * size + kk5] * b[kk5 * size + jj];
							}
							c[ii5 * size + jj] = save5;
                                                }

						if(ii6 < size && ii6 < i + t) {
							save6 = c[ii6 * size + jj];
							for(kk6 = k ; kk6 < size && kk6 < k + t ; kk6++) {
								save6 = save6 + a[ii6 * size + kk6] * b[kk6 * size + jj];
							}
							c[ii6 * size + jj] = save6;
                                                }

						if(ii7 < size && ii7 < i + t) {
							save7 = c[ii7 * size + jj];
							for(kk7 = k ; kk7 < size && kk7 < k + t ; kk7++) {
								save7 = save7 + a[ii7 * size + kk7] * b[kk7 * size + jj];
							}
							c[ii7 * size + jj] = save7;
                                                }

						if(ii8 < size && ii8 < i + t) {
							save8 = c[ii8 * size + jj];
							for(kk8 = k ; kk8 < size && kk8 < k + t ; kk8++) {
								save8 = save8 + a[ii8 * size + kk8] * b[kk8 * size + jj];
							}
							c[ii8 * size + jj] = save8;
                                                }

                                        }
                                }
                        }
                }
        }

}

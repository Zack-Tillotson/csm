Zack Tillotson
May 2012

Advanced Architecture - My Implementation Is Faster Than Yours

The program code has been copied into several similar .c files. Each program is labeled according to which step 
in the directions it corresponds with. For example, prog3.c will compile into prog3, and corresponds with question 
#3. Question 8 has been broken into each step 1-5, and the code is labeled prog8#.c. For example, step 2 is prog82.c
and compiles into prog82.

To only compile: 
$ make

To compile and run all programs (takes a long time)
$ make run

An example run (partial) :

$ make run
rm prog2 prog3 prog4 prog5 prog6 prog7 prog81 prog82 prog83 prog84 prog85 | echo "Deleting what I can"
Deleting what I can
gcc -o prog2 prog2.c
gcc -o prog3 -lcblas -lblas prog3.c
gcc -o prog4 -O1 prog2.c
gcc -o prog5 -O2 prog2.c
gcc -o prog6 -O3 prog2.c
gcc -o prog7 -O3 -funroll-loops prog2.c
gcc -o prog81 -lcblas -lblas prog81.c
gcc -o prog82 -lcblas -lblas prog82.c
gcc -o prog83 -lcblas -lblas prog83.c
gcc -o prog84 -lcblas -lblas prog84.c
gcc -o prog85 -lcblas -lblas -O5 prog85.c
./prog2
Starting multiplication [size 500]
Finished multiplication [time 659]

Starting multiplication [size 1000]
Finished multiplication [time 8312]

Starting multiplication [size 1500]
...
...
...

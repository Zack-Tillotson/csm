mpiCC -o Jacobi Jacobi.cpp
mpirun -v -np 4 Jacobi 
mpirun -v -np 4 Jacobi -r

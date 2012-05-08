all: clean prog2 prog3 prog4 prog5 prog6 prog7 prog8

prog2:
	gcc -o prog2 prog2.c

prog3:
	gcc -o prog3 -lcblas -lblas prog3.c

prog4:
	gcc -o prog4 -O1 prog2.c

prog5:
	gcc -o prog5 -O2 prog2.c

prog6:
	gcc -o prog6 -O3 prog2.c

prog7:
	gcc -o prog7 -O3 -funroll-loops prog2.c

prog8: prog81 prog82 prog83 prog84 prog85

prog81:
	gcc -o prog81 -lcblas -lblas prog81.c

prog82:
	gcc -o prog82 -lcblas -lblas prog82.c

prog83:
	gcc -o prog83 -lcblas -lblas prog83.c

prog84:
	gcc -o prog84 -lcblas -lblas prog84.c

prog85:
	gcc -o prog85 -lcblas -lblas -O5 prog85.c

clean:
	rm prog2 prog3 prog4 prog5 prog6 prog7 prog81 prog82 prog83 prog84 prog85 | echo "Deleting what I can"

run: all
	./prog2
	./prog3
	./prog4
	./prog5
	./prog6
	./prog7
	./prog81
	./prog82
	./prog83
	./prog84
	./prog85

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

prog8:
	gcc -o prog8 prog8.c

clean:
	rm prog2 prog3 prog4 prog5 prog6 prog7 prog8 | echo "Deleting what I can"

run: all
	./prog2
	./prog3
	./prog4
	./prog5
	./prog6
	./prog7
	./prog8

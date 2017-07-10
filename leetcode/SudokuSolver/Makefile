cpp_Sudoku: solveSudoku.h main.cpp
	g++-7.1 -o main main.cpp -g -Wall

c_Sudoku: solveSudoku.o main.o
	gcc -o main solveSudoku.o main.o -g -Wall -std=c99

solveSudoku.o: solveSudoku.c solveSudoku.h
	gcc -c solveSudoku.c -g -Wall -std=c99

main.o: main.c solveSudoku.h
	gcc -c main.c -g -Wall -std=c99

clean:
	rm *.o main

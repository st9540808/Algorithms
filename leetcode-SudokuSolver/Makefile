PROGRAM: solveSudoku.o main.o
	gcc -o main solveSudoku.o main.o -g -Wall -std=c99

solveSudoku.o: solveSudoku.c solveSudoku.h
	gcc -c solveSudoku.c -g -Wall -std=c99

main.o: main.c solveSudoku.h
	gcc -c main.c -g -Wall -std=c99

clean:
	-rm *.o $(object) solveSudoku

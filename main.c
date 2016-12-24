#include <stdio.h>
#include <stdlib.h>
#include "solveSudoku.h"

void printOut(char** board);

char input[9][9] =
	{"53..7....", //0
	 "6..195...", //1
	 ".98....6.", //2
	 "8...6...3", //3
	 "4..8.3..1", //4
	 "7...2...6", //5
	 ".6....28.", //6
	 "...419..5", //7
	 "....8..79"};//8
	//012345678


int main()
{
	char **array;
	array = malloc(9 * sizeof(char *)); 
	for(int i = 0; i < 9; i++)
	{
		array[i] = malloc(9 * sizeof(char));
		if(array[i] == NULL){
			fprintf(stderr, "out of memory\n");
			exit(EXIT_FAILURE);
		}
	}

	for(int i = 0; i < 9; ++i)
		for(int j = 0; j < 9; ++j)
			array[i][j] = input[i][j];
	
	solveSudoku(array, 9, 9);
	printOut(array);

	for(int i = 0; i < 9; ++i) 
		free(array[i]);  
	free(array);  
	return 0;
}


void printOut(char** board)
{
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if( j % 3 == 0 )
                printf(" ");
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

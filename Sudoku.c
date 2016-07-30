#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void solveSudoku(char** board, int boardRowSize, int boardColSize);
bool validAnsExist(char** board, int row, int col);
bool isValid(char** board, char testAns, int row, int col);

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


void solveSudoku(char** board, int boardRowSize, int boardColSize)
{
	char map[9][9]; 
	for(int i = 0; i < 9; ++i) 
		for(int j = 0; j < 9; ++j)
			map[i][j] = board[i][j];

	int row = 0, col = 0;
	while( map[row][col] != '.' )//initialize to the location of first blank in map[][]
	{	
		++col;
		if( col == 9 ){	++row; col = 0;	if(row == 9) break;}
    	}

	while( row != 9 && row != -1 )//start backtracking
	{
		if( validAnsExist(board, row, col) )
		{
			do
			{
				++col;
				if( col == 9 ){	++row; col = 0;if(row == 9) break;}
			}while( map[row][col] != '.' );
		}
        	else
        	{
			do
			{
				--col;
				if( col == -1 ){ --row; col = 8;if(row == -1) break;}
			}while( map[row][col] != '.' );
        	}
	}//end of back tracking
}

bool validAnsExist(char** board, int row, int col)
{
	if( board[row][col] == '.' )
	{
		for(char testAns = '1'; testAns <= '9'; ++testAns)
		{
			if( isValid(board, testAns, row, col) )
			{
				board[row][col] = testAns;
				return true;
			}
		}
    }
    else
   	{
    	for(char testAns = board[row][col] + 1; testAns <= '9'; ++testAns)
    	{
    		if( isValid(board, testAns, row, col) )
			{
				board[row][col] = testAns;
				return true;
			}
		}
	}
    
	board[row][col] = '.';
	return false;	
}

bool isValid(char** board, char testAns, int row, int col)
{
	//verify row
	for(int i = 0; i < 9; ++i)
		if( testAns != '.' && i != col && board[row][i] == testAns )
			return false;
   
	//verify column
	for(int i = 0;i < 9; ++i)
		if( testAns != '.' && i != row && board[i][col] == testAns )
			return false;

	//verify cell
	for(int i = 3*(row/3); i < 3*(row/3)+3; ++i)
		for(int j = 3*(col/3); j < 3*(col/3)+3; ++j)
		{
			if( row == i && col == j )
				continue;
			if( testAns != '.' && board[i][j] == testAns )
				return false;
		}

	return true;
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

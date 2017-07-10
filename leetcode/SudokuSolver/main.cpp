#include <iostream>
#include <vector>
#include "solveSudoku_cpp.h"

using std::cout;
using std::endl;

char input[][10] =
{
	"53..7....", //0
	"6..195...", //1
	".98....6.", //2
	"8...6...3", //3
	"4..8.3..1", //4
	"7...2...6", //5
	".6....28.", //6
	"...419..5", //7
	"....8..79", //8
};

int main()
{
	vector<vector<char>> board(9, vector<char>(9));
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j)
			board[i][j] = input[i][j];
	
	Solution solve;
	solve.solveSudoku(board);

	for (int i = 0; i < 9; ++i)	{
		for (int j = 0; j < 9; ++j)
		{
			if (j % 3 == 0)
				cout << " ";
			cout << board[i][j];
		}
		cout << "\n";
	}
	
	return 0;
}

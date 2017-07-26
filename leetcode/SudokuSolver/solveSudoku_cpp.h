#include <iostream>
#include <vector>
template <typename T>
using vector = std::vector<T>;


class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
		vector<vector<char>> map = board;

		for (vector<char>& row : board) {
			for (char& elem : row)
				if (elem == '.') elem = '0';
		}

		int row = 0, col = 0;
		while (map[row][col] != '.') { // initialize to the location of first blank in map[][]
			++col;
			if (col == 9) { ++row; col = 0; if (row == 9) break;}
		}
	
		while (row != 9 && row != -1) { // start backtracking
			if (validAnsExist(board, row, col)) {
				do {
					++col;
					if (col == 9) {	++row; col = 0; if (row == 9) break;}
				} while (map[row][col] != '.');
			} else {
				do {
					--col;
					if (col == -1) { --row; col = 8; if (row == -1) break;}
				} while (map[row][col] != '.');
			}
		} // end of back tracking
    }

private:
	bool validAnsExist(vector<vector<char>>& board, int row, int col) {
		for (char testAns = board[row][col] + 1; testAns <= '9'; testAns++) {
			if (isValid(board, testAns, row, col)) {
				board[row][col] = testAns;
				return true;
			}
		}
	
		board[row][col] = '0';
		return false;
	}
	
	bool isValid(const vector<vector<char>> &board, char testAns, int row, int col) const {
		// verify row
		for (int i = 0; i < 9; i++)
			if (board[row][i] == testAns)
				return false;
	
		// verify column
		for (int i = 0; i < 9; i++)
			if (board[i][col] == testAns)
				return false;
	
		// verify cell
		for (int i = 3 * (row / 3); i < 3 * (row / 3) + 3; i++)
			for (int j = 3 * (col / 3); j < 3 * (col / 3) + 3; j++)
				if (board[i][j] == testAns)
					return false;
	
		return true;
	}
};

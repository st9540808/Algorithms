#include <iostream>
#include <string>
#include <vector>
template <typename T>
using vector = std::vector<T>;
using string = std::string;


#include <utility>

class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> answers;
		vector<string> board(n, string(n, '.'));
		solve(answers, board, n, 0);
		return std::move(answers);
	}

private:
	void solve(vector<vector<string>>& answers,
	           vector<string>& board,
	           int n,
	           int col) {
		if (col == n) {
			answers.push_back(board);
			return;
		}
		for (int i = 0; i < n; i++) {
			if (is_legal_placement(board, n, i, col)) {
				board[i][col] = 'Q';
				solve(answers, board, n, col + 1);
				board[i][col] = '.';
			}
		}
	}

	bool is_legal_placement(vector<string>& board, int n, int row, int col) {
		// check row
		for (int i = 0; i < n; i++) {
			if (board[row][i] == 'Q')
				return false;
		}

		// check 315 degree diagonal
		for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--) {
			if (board[i][j] == 'Q')
				return false;
		}

		// check 135 degree diagonal
		for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
			if (board[i][j] == 'Q')
				return false;
		}

		return true;
	}
};


int main()
{
	Solution sol;
	auto answers = sol.solveNQueens(10);
	
	for (const vector<string> &row : answers) {
		for (string str : row)
			std::cout << str << std::endl;
		std::cout << std::endl;
	}

	return 0;
}

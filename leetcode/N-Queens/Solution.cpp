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
		answers.clear();
		this->n = n;
		allocate(n);
		solveNQueens_recur(0);
		deallocate(n);
		return std::move(answers);
	}

private:
	int n;
	bool **board;
	vector<vector<string>> answers;

	void solveNQueens_recur(int col) {
		for (int i = 0; i < this->n; i++) {
			bool legal_placement = is_legal_placement(i, col);
			if (legal_placement && col == this->n - 1) {
				this->board[i][col] = true;
				store_answer();
			} else if (legal_placement) {
				this->board[i][col] = true;
				solveNQueens_recur(col + 1);
			}
			this->board[i][col] = false;
		}
	}

	bool is_legal_placement(const int row, const int col) {
		// check row
		for (int i = 0; i < this->n; i++) {
			if (board[row][i] == true)
				return false;
		}

		// check diagonal
		int base_row = 0, base_col = 0;
		if (row < col)
			base_col = col - row;
		else if (row > col)
			base_row = row - col;

		for (int i = base_row, j = base_col; is_within_boundary(i, j); i++, j++) {
			if (board[i][j] == true)
				return false;
		}

		base_row = 0; base_col = this->n - 1;
		if (row + col < this->n - 1)
			base_col = row + col;
		else if (row + col > this->n - 1)
			base_row = row + col - (this->n - 1);

		for (int i = base_row, j = base_col; is_within_boundary(i, j); i++, j--) {
			if (board[i][j] == true)
				return false;
		}

		return true;
	}

	inline bool is_within_boundary(int i, int j) {
		return (0 <= i && i < this->n) && (0 <= j && j < this->n);
	}

	void store_answer() {
		vector<string> answer(n);
		for (int i = 0; i < this->n; i++) {
			string answer_row(this->n, '.');
			for (int j = 0; j < this->n; j++) {
				if (board[i][j] == true)
					answer_row.at(j) = 'Q';
			}
			answer.at(i) = answer_row;
		}
		this->answers.push_back(answer);
	}

	void allocate(int n) {
		this->board = new bool*[n];
		for (int i = 0; i < n; i++)
			this->board[i] = new bool[n]();
	}

	void deallocate(int n) {
		for (int i = 0; i < n; i++)
			delete [] this->board[i];
		delete [] this->board;
	}

	void print() { // debug
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				std::cout << this->board[i][j] << " ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};


int main()
{
	Solution sol;
	auto answers = sol.solveNQueens(4);
	
	for (const vector<string> &row : answers) {
		for (string str : row)
			std::cout << str << std::endl;
		std::cout << std::endl;
	}

	return 0;
}

#include <iostream>
#include <vector>
template <typename T>
using vector = std::vector<T>;


#include <utility>

class Solution {
public:
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> matrix(n, vector<int>(n));
		generateMatrix_recur(matrix, n, 0, 1);
		return std::move(matrix);
	}

private:
	struct position {
		int i;
		int j;
		position(int init_position)
		: i(init_position), j(init_position)
		{}
		inline void move_right() { this->j++; };
		inline void move_left()  { this->j--; };
		inline void move_down()  { this->i++; };
		inline void move_up()    { this->i--; };
	};

	void generateMatrix_recur(vector<vector<int>>& matrix, int dimension, int init_position, int value) {
		if (dimension == 0) return;
		if (dimension == 1) {
			matrix[init_position][init_position] = value;
			return;
		} else {
			position pos(init_position);

			iterate_and_assign(matrix, pos, dimension, value, &position::move_right);
			iterate_and_assign(matrix, pos, dimension, value, &position::move_down);
			iterate_and_assign(matrix, pos, dimension, value, &position::move_left);
			iterate_and_assign(matrix, pos, dimension, value, &position::move_up);
			
			generateMatrix_recur(matrix, dimension - 2, init_position + 1, value);
		}
	}

	inline void iterate_and_assign(vector<vector<int>>& matrix
			, position& pos, int dimension, int& value, void (position::*move)()) {
		for (int i = 0; i < dimension - 1; i++) {
			matrix[pos.i][pos.j] = value++;
			(pos.*move)();
		}
	}
};


int main()
{
	Solution sol;
	auto matrix = sol.generateMatrix(5);
	
	for (const vector<int> &row : matrix) {
		for (int element : row)
			std::cout << element << ", ";
		std::cout << std::endl;
	}

	return 0;
}

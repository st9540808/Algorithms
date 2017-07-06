#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
using vector = std::vector<T>;

class Solution {
public:
	// time complexity O(m+n)
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.size() == 0 || matrix.at(0).size() == 0)
			return false;

		int i = 0, j = matrix[0].size() - 1;
		auto is_within_boundary = [&matrix](int i, int j) {
			return i < matrix.size() && j >= 0;
		};
		
		while (is_within_boundary(i, j) && matrix[i][j] != target) {
			if (target > matrix[i][j])
				i++;
			else
				j--;
		}
		if (is_within_boundary(i, j))
			return true;
		return false;
	}

	// time compexity O(mlgn)
    bool _searchMatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.size() == 0 || matrix.at(0).size() == 0)
			return false;

		auto is_within_range = [target](const vector<int> &row) {
			return row.front() <= target
				&& row.back() >= target;
		};

		for (const vector<int> &row : matrix) {
			if (is_within_range(row)
					&& std::binary_search(row.begin(), row.end(), target))
				return true;
		}
		return false;
    }
};


int main()
{
	std::vector<std::vector<int>> matrix(5, std::vector<int>(5));
	matrix = {
		{1, 4, 7, 11, 15},
		{2, 5, 8, 12, 19},
		{3, 6, 9, 16, 22},
		{10, 13, 14, 17, 24},
		{18, 21, 23, 26, 30}
	};

	std::vector<std::vector<int>> matrix_empty(0, std::vector<int>(0));
	matrix_empty = {
		{}
	};

	Solution sol;
	std::cout << sol.searchMatrix(matrix, 13);
}

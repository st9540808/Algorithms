#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <math.h>
using namespace std;

/* funtion prototype here */
class SquareMatrix
{
public:
	SquareMatrix(int n) : matrix(n, vector<int>(n))
	{}

	friend istream& operator>>(istream& is, SquareMatrix& obj);
	friend ostream& operator<<(ostream& os, const SquareMatrix& obj);

	int determinant() { return determinant(this->matrix); }
	int determinant(const vector<vector<int>>& matrix) const
	{
		if (matrix.size() == 1) return matrix[0][0];

		int sum = 0;
		for (decltype(matrix.size()) i = 0; i < matrix.size(); ++i)
		{
			vector<vector<int>> M_1j(matrix.size() - 1,
			                         vector<int>(matrix.size() - 1));
			for (decltype(matrix.size()) j = 1, M_i = 0; j < matrix.size(); ++j)
				for (decltype(matrix.size()) k = 0, M_j = 0; k < matrix.size(); ++k)
					if (k != i)
					{
						M_1j[M_i][M_j++] = matrix[j][k];
						if (M_j == matrix.size() - 1) { M_i++; M_j = 0; }
					}
			if (i % 2 == 0)
				sum +=  matrix[0][i] * determinant(M_1j);
			else
				sum += -matrix[0][i] * determinant(M_1j);
		}
		return sum;
	}

	void permutation()
	{
		vector<int> perm {3, 4, 1, 2};
		for (decltype(perm.size()) i = 0; i < perm.size(); ++i)
			if (&matrix.at(i) != &matrix.at(perm.at(i) - 1))
			{
				iter_swap(matrix.begin() + i,
				          matrix.begin() + (perm.at(i) - 1));
				swap(perm.at(i), perm.at(perm.at(i) - 1));
			}
	}

private:
	vector<vector<int>> matrix;
	class GaussElimination
	{
	};
};

istream& operator>>(istream& is, SquareMatrix& obj)
{
	for (auto& row : obj.matrix)
		for (auto& col : row)
		{
			int input; cin >> input;
			col = input;
		}
	return is;
}

ostream& operator<<(ostream& os, const SquareMatrix& obj)
{
	for (const auto& row : obj.matrix)
	{
		for (const auto& col : row)
			cout << col << " ";
		cout << "\n";
	}
	return os;
}


int main()
{
	int n;
	while (cin >> n, n > 0)
	{
		SquareMatrix matrix(n);

		cin  >> matrix;
		cout << matrix.determinant() << "\n";
	}

	cout << "*";
	return 0;
}

#include "Matrix.h"

int main()
{
	Matrix<int> matInt1(5, 5);
	Matrix<int> matInt2(6, 6);
	std::cin  >> matInt1;
	std::cin  >> matInt2;
	std::cout << matInt1 << "\n";
	std::cout << matInt2 << "\n";
	auto matSum = matInt1 + matInt2;
	std::cout << matSum << "\n";

	return 0;
}

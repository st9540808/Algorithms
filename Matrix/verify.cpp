#include "Matrix.h"

int main()
{
	Matrix<int> matInt(5, 5);
	std::cin  >> matInt;
	std::cout << std::move(matInt);

	return 0;
}

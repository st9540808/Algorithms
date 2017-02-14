#include <stdio.h>
#include <stdlib.h>

int det(int n, int A[][n])
{
	if (n == 1) return A[0][0];

	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		int A_1j[n-1][n-1], *p = &A_1j[0][0];
		for (int j = 1; j < n; ++j)
			for (int k = 0; k < n; ++k)
				if (k != i) *p++ = A[j][k];
		
		if (i % 2 == 0)
			sum +=  A[0][i] * det(n-1, A_1j);
		else
			sum += -A[0][i] * det(n-1, A_1j);
	}
	return sum;
}

int main()
{
	int array[3][3] =
	{
		{1,2,3},
		{4,1,6},
		{7,8,2}
	};
	printf("%d\n", det(3, array));

	return 0;
}

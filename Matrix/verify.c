#include <stdio.h>
#include "det.h"

int main()
{
	int n;
	while (scanf("%d", &n), n != 0)
	{
		int matrix[n][n]; 
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				scanf("%d", &matrix[i][j]);
		printf("%d\n", det(n, matrix));
	}
	puts("*");
}

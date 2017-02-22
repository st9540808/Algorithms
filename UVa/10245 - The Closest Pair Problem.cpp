#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point_ { double x, y; } point;
point allPoints[10000];

inline int point_cmp(const void *p1, const void *p2)
{
	return ((point *)p1)->x > ((point *)p2)->x;
}

inline double squared_dist(const point p1, const point p2)
{
	return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}


int main()
{
	int size;
	while (scanf("%d", &size), size != 0)
	{
		for (int i = 0; i < size; ++i)
			scanf("%lf %lf", &allPoints[i].x, &allPoints[i].y);

		qsort(allPoints, size, sizeof(point), point_cmp);

		double minimumSquared = 10000. * 10000.;
		for (int i = 0; i < size; ++i)
			for (int j = i + 1; j < size; ++j)
			{
				double dist = squared_dist(allPoints[i], allPoints[j]);
				if (dist < minimumSquared)
				{
					minimumSquared = dist;
					break;
				}
			}
		for (int i = size - 1; i >= 0; --i)
			for (int j = i - 1; j >= 0; --j)
			{
				double dist = squared_dist(allPoints[i], allPoints[j]);
				if (dist < minimumSquared)
				{
					minimumSquared = dist;
					break;
				}
			}

		if (minimumSquared == 10000. * 10000.)
			printf("INFINITY\n");
		else
			printf("%.4f\n", sqrt(minimumSquared));
	}

	return 0;
}

#include <math.h>

typedef float (*Shape)(float x, float y, float r);

float circle(float x, float y, float r)
{
	return pow(x, 2) + pow(y, 2) - pow(r, 2);
}
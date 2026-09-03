#include "types.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

float Vector2Distance(Vector2 a, Vector2 b)
{
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

Vector2 Vector2Sub(Vector2 a, Vector2 b)
{
	return (Vector2){a.x - b.x, a.y - b.y};
}

float randRange(float min, float max)
{
	return min + (max - min) * ((float)rand() / RAND_MAX);
}
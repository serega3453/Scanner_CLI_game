#ifndef TYPES_H
#define TYPES_H

typedef struct
{
	float x;
	float y;
} Vector2;

float randRange(float min, float max);

float Vector2Distance(Vector2 a, Vector2 b);

Vector2 Vector2Sub(Vector2 a, Vector2 b);

#endif
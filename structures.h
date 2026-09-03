#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "types.h"

typedef struct
{
	Vector2 position;
	float signatureSize;
	int id;
	bool alive;
	const char* color;
} Object;

typedef struct
{
	Vector2 origin;
	Vector2 direction;
} Ray;

typedef struct
{
	Object* items;
	int count;
	int capacity;
} ObjectArray;

typedef struct
{
	int* items;
	int count;
	int capacity;
} IntArray;

#endif
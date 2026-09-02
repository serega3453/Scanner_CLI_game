#include "shapes.h"
#include "types.h"

typedef struct
{
	Vector2 position;
	Shape shape;
	float signatureSize;
	int id;
	bool alive;
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
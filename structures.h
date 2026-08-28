#include "shapes.h"
#include "types.h"

typedef struct
{
	Vector2 position;
	Shape shape;
	float signatureSize;
	int id;
} Object;

typedef struct
{
	Vector2 origin;
	Vector2 direction;
} Ray;
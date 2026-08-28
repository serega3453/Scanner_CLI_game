typedef struct
{
	float x;
	float y;
} Vector2;

float Vector2Distance(Vector2 a, Vector2 b)
{
	return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
}

Vector2 Vector2Sub(Vector2 a, Vector2 b)
{
	return (Vector2){a.x - b.x, a.y - b.y};
}
typedef struct
{
	float x;
	float y;
} Vector2;

float Vector2Distance(Vector2 a, Vector2 b)
{
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

Vector2 Vector2Sub(Vector2 a, Vector2 b)
{
	return (Vector2){a.x - b.x, a.y - b.y};
}
#include "array.h"
#include <float.h>
#include <stdbool.h>

bool Raycast(Ray ray, Object target)
{
    Vector2 localPosition = Vector2Sub(ray.origin, target.position);
    
    float a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;
    float b = 2 * (localPosition.x * ray.direction.x + localPosition.y * ray.direction.y);
    float c = localPosition.x * localPosition.x + localPosition.y * localPosition.y - target.signatureSize * target.signatureSize;
    
    float d = b * b - 4 * a * c;
    
    if (d < 0) return false;
    
    float t1 = (-b - sqrt(d)) / (2 * a);
    float t2 = (-b + sqrt(d)) / (2 * a);
    
    if (t1 > 0) return true;
    if (t2 > 0) return true;
    return false;
}

bool raycastPoll(Ray ray, ObjectArray* objects, Object** hit, bool* collision)
{
    float maxDist = 50;
    float closestDist = FLT_MAX;
    *collision = false;

    for (int i = 0; i < objects->count; i++)
    {
        float dist = Vector2Distance(ray.origin, objects->items[i].position);
        if (dist < maxDist)
        {
            if (Raycast(ray, objects->items[i]))
            {
                if (dist < closestDist)
                {
                    closestDist = dist;
                    *hit = &objects->items[i];
                }
                if (dist <= objects->items[i].signatureSize + 1)
                {
                    *collision = true;
                }
            }
        }
    }

    if (closestDist == FLT_MAX)
    {
        return false;
    }
	return true;
}

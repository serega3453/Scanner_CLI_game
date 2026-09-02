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

bool PointcastHit(Vector2 point, ObjectArray* objects, Object** hit)
{
    for (int i = 0; i < objects->count; i++)
    {
        if (Vector2Distance(point, objects->items[i].position) < objects->items[i].signatureSize)
        {
            return true;
            *hit = &objects->items[i];
        }
    }
    return false;
}

bool Pointcast(Vector2 point, ObjectArray* objects)
{
    for (int i = 0; i < objects->count; i++)
    {
        if (Vector2Distance(point, objects->items[i].position) < objects->items[i].signatureSize)
        {
            return true;
        }
    }
    return false;
}

bool bounds(Vector2 point, Vector2 range)
{
    if (((point.x > -range.x/2) && (point.x < range.x/2)) && ((point.y > -range.y/2) && (point.y < range.y/2)))
    {
        return true;
    }
    return false;
}
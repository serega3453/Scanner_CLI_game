#include "array.h"
#include <float.h>
#include <stdbool.h>

bool Raycast(Ray ray, Object target)
{
    Vector2 localPosition = Vector2Sub(ray.origin, target.position);
    
    float a = pow(ray.direction.x, 2) + pow(ray.direction.y, 2);
    float b = 2 * (localPosition.x * ray.direction.x + localPosition.y * ray.direction.y);  // минус!
    float c = pow(localPosition.x, 2) + pow(localPosition.y, 2) - pow(target.signatureSize, 2);
    
    float d = pow(b, 2) - 4 * a * c;
    
    if (d < 0) return false;
    
    float t1 = (-b - sqrt(d)) / (2 * a);
    float t2 = (-b + sqrt(d)) / (2 * a);
    
    if (t1 > 0) return true;
    if (t2 > 0) return true;
    return false;
}

bool raycastPoll(Ray ray, ObjectArray* objects, Object** hit)
{
    float maxDist = 50;
    float closestDist = FLT_MAX;
	for (int i = 0; i < objects->count; i++)
	{
		if (Raycast(ray, objects->items[i]))
		{
			float dist = Vector2Distance(ray.origin, objects->items[i].position);
            if (dist < maxDist)
            {
                if (dist < closestDist)
                {
                    closestDist = dist;
                    *hit = &objects->items[i];
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

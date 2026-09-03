#ifndef RAYCAST_H
#define RAYCAST_H

#include "array.h"
#include <float.h>
#include <stdbool.h>

bool Raycast(Ray ray, Object target);

bool raycastPoll(Ray ray, ObjectArray* objects, Object** hit, bool* collision, float renderDistance);

bool PointcastHit(Vector2 point, ObjectArray* objects, Object** hit);

bool Pointcast(Vector2 point, ObjectArray* objects);

bool bounds(Vector2 point, Vector2 range);

#endif
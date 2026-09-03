#ifndef GAME_H
#define GAME_H

#include "array.h"

void createObjects(ObjectArray* objects, int maxObjects, float mapX, float mapY);

void init(void);

Object* rendering(float scanStart, float scanStop, float scanStep, float playerTurn, Vector2 playerPos, ObjectArray* objects);

void simulation(ObjectArray* objects);

#endif
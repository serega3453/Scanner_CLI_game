#ifndef ARRAY_H
#define ARRAY_H

#include "structures.h"
#include <stdlib.h>

void addObject(ObjectArray* arr, Object obj);

void RemoveObjectByIndex(ObjectArray* arr, int index);

void RemoveObjectById(ObjectArray *arr, int id);

void FreeObjects(ObjectArray* arr);

void addInt(IntArray* arr, int i);

void RemoveInt(IntArray* arr, int index);

void FreeInts(IntArray* arr);

#endif
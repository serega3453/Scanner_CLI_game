#include "structures.h"
#include <stdlib.h>

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

void addObject(ObjectArray* arr, Object obj)
{
	if (arr->count >= arr->capacity)
	{
		arr->capacity = arr->capacity ? arr->capacity * 2 : 4;
		arr->items = realloc(arr->items, arr->capacity * sizeof(Object));
	}
	arr->items[arr->count++] = obj;
}

void RemoveObject(ObjectArray* arr, int index) 
{
    for (int i = index; i < arr->count - 1; i++)
        arr->items[i] = arr->items[i + 1];
    arr->count--;
}

void FreeObjects(ObjectArray* arr) 
{
    free(arr->items);
    arr->items = NULL;
    arr->count = 0;
    arr->capacity = 0;
}

void addInt(IntArray* arr, int i)
{
	if (arr->count >= arr->capacity)
	{
		arr->capacity = arr->capacity ? arr->capacity * 2 : 4;
		arr->items = realloc(arr->items, arr->capacity * sizeof(int));
	}
	arr->items[arr->count++] = i;
}

void RemoveInt(IntArray* arr, int index) 
{
    for (int i = index; i < arr->count - 1; i++)
        arr->items[i] = arr->items[i + 1];
    arr->count--;
}

void FreeInts(IntArray* arr) 
{
    free(arr->items);
    arr->items = NULL;
    arr->count = 0;
    arr->capacity = 0;
}
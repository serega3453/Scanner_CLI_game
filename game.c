#include "game.h"
#include "config.h"
#include <time.h>
#include "array.h"
#include "menu.h"
#include <stdio.h>
#include <math.h>
#include "raycast.h"

void createObjects(ObjectArray* objects, int maxObjects, float mapX, float mapY)
{
	addObject(objects, (Object){(Vector2){0,0}, 10, -1, true});

	int tryCount = 0;

	while (objects->count < maxObjects + 1)
	{
		if (tryCount >= 1000)
		{
			printf("\n\nCould not create more than %d objects.\n\n", objects->count);
			exit(0);
		}

		Vector2 tryPos = {randRange(floor(-mapX/2), ceil(mapX/2)), randRange(floor(-mapY/2), ceil(mapY/2))};

		if (!Pointcast(tryPos, objects) && bounds(tryPos, (Vector2){mapX-5, mapY-5}))
		{
			addObject(objects, (Object)
			{
				.position = tryPos,
				.signatureSize = randRange(1, 10), 
				.id = objects->count, 
				.alive = true,
				.color = colors[(objects->count * 7) % 10]
			});

			tryCount = 0;
		}

		tryCount++;
	}
	RemoveObjectByIndex(objects, 0);
}

void init(void)
{
	FreeObjects(&objects);

	srand(time(NULL));

	if (touched.items) 
	{
    	free(touched.items);
    	touched.items = NULL;
    }

    touched.count = 0;
    touched.capacity = 0;

    settings();

    printf("Current state: %f\n",mapX);
    printf("Enter desired X map size:\n");
    scanf("%f", &mapX);

	printf("Current state: %f\n", mapY);
    printf("Enter desired Y map size:\n");
    scanf("%f", &mapY);

    printf("Current state: %d\n", maxObjects);
    printf("Enter desired object count:\n");
    scanf("%d", &maxObjects);

    createObjects(&objects, maxObjects, mapX, mapY);

    printf("GAME STARTED...");
}

void simulation(ObjectArray* objects)
{
	for (int i = 0; i < objects->count; i++)
	{
		if (randRange(1, 10) <= 2 && objects->items[i].alive)
		{
			Vector2 nextPos = objects->items[i].position;
			nextPos.x += randRange(-2, 2);
			nextPos.y += randRange(-2, 2);

			if (!Pointcast(nextPos, objects) && bounds(nextPos, (Vector2){mapX, mapY}))
			{
				objects->items[i].position = nextPos;
			}
		}
	}
}

Object* rendering(float scanStart, float scanStop, float scanStep, float playerTurn, Vector2 playerPos, ObjectArray* objects)
{
	Object* hit;
	Object* collisionObject = NULL;
	bool collision;
	for (int i = scanStart; i < scanStop; i += scanStep)
	{
		float rad = (i + 180 + playerTurn) * 3.14159 / 180;
		float math_rad = rad + 3.14159/2;

		if (i % 45 == 0)
		{
			//printf("|%d|", i);
			printf("|");
		}

		if (raycastPoll((Ray){.origin = playerPos, .direction = {-cos(math_rad), sin(math_rad)}}, objects, &hit, &collision, renderDistance))
		{

			printf("%s%d\033[0m", hit->color, abs(hit->id % 10));

			if (collision)
			{
				collisionObject = hit;
			}
		}
		else
		{
			printf(".");
		}
	}
	printf("\n\n");

	return collisionObject;
}
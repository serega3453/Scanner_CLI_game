#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "raycast.h"
#include "terminal.h"
#include <ctype.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define RESET "\033[30m"

const char* colors[] = 
{
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	BRIGHT_RED,
	BRIGHT_GREEN,
	BRIGHT_YELLOW,
	BRIGHT_BLUE,
	RESET
};

float randRange(float min, float max)
{
	return min + (max - min) * ((float)rand() / RAND_MAX);
}

void header_print(float step)
{
	printf("Speed: %10.1f\n", step);
}

void footer_print(float step, float turnStep, Object* collision)
{
	printf("%-15s%10.1f\n", "Speed: ", step);
	printf("%-15s%10.1f\n", "Turn speed: ", turnStep);
	if (collision != NULL)
	{
		printf("%-15s%10d\n", "Touching: ", collision->id);
	}
	else
	{
		printf("%-15s%10s\n", "Touching: ", "nothing");
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
			printf("|%d|", i);
		}

		if (raycastPoll((Ray){.origin = playerPos, .direction = {-cos(math_rad), sin(math_rad)}}, objects, &hit, &collision))
		{
			printf("%s%d\033[0m", colors[abs((hit->id * 7) % 10)], abs(hit->id % 10));
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

void cycle(void)
{
	srand(time(NULL));

	ObjectArray objects = {NULL, 0, 0};

	for (int i = 0; i < 1000; i++)
	{
		addObject(&objects, (Object){.position = {randRange(-1000, 1000), randRange(-1500, 1500)}, .shape = circle, .signatureSize = randRange(1, 10), .id = i});
	}

	Vector2 playerPos = {0, 0};
	float playerTurn = 180;
	float step = 0.5;
	float turnStep = 2;

	int scanStart = 0;
	int scanStop = 360;
	int scanStep = 2;

	int renderMode = 0;
	int scanMode = 360;
	printf("1 - one line, 0 - not one line\n");
	scanf("%d", &renderMode);

	printf("1 - 360 scan, 0 - 180 scan\n");
	scanf("%d", &scanMode);

	if (scanMode == 0)
	{
		scanStart = 90;
		scanStop = 270;
		scanStep = 1;
	}

	terminal_init();

    printf("GAME STARTED...");

	while(1)
	{
		if (renderMode == 1)
		{
			terminal_clear();
		}

		//header_print(step);

		Object* collision = rendering(scanStart, scanStop, scanStep, playerTurn, playerPos, &objects);

		footer_print(step, turnStep, collision);

		float angleRad = playerTurn * 3.14159 / 180;

		int ch = terminal_getch();
		ch = tolower(ch);

		switch (ch)
		{
			case 'r':
				step += 0.1;
				break;
			case 'f':
				step -= 0.1;
				break;
			case 't':
				turnStep += 0.1;
				break;
			case 'g':
				turnStep -= 0.1;
				break;
			case 'w':
				playerPos.x += sin(angleRad) * step;
				playerPos.y += cos(angleRad) * step;
				break;
			case 's':
				playerPos.x -= sin(angleRad) * step;
				playerPos.y -= cos(angleRad) * step;
				break;
			case 'a':
				playerPos.x -= cos(angleRad) * step;
				playerPos.y += sin(angleRad) * step;
				break;
			case 'd':
				playerPos.x += cos(angleRad) * step;
				playerPos.y -= sin(angleRad) * step;
				break;
			case 'e':
				playerTurn += turnStep;
				break;
			case 'q':
				playerTurn -= turnStep;
				break;
			case ' ':
				break;
			case 27:
				terminal_restore();
				return;
				break;
		}
	}
}

int main(void)
{
	cycle();

	return 0;
}

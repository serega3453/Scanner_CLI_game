#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "raycast.h"
#include "terminal.h"

float randRange(float min, float max)
{
	return min + (max - min) * ((float)rand() / RAND_MAX);
}

void cycle(void)
{
	srand(time(NULL));

	ObjectArray objects = {NULL, 0, 0};

	for (int i = 0; i < 2000; i++)
	{
		addObject(&objects, (Object){.position = {randRange(-1500, 1500), randRange(-10, 10)}, .shape = circle, .signatureSize = randRange(1, 1), .id = i});
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
		int ch = terminal_getch();

		if (renderMode == 1)
		{
			terminal_clear();
		}

		float angleRad = playerTurn * 3.14159 / 180;

		if (ch == 'w' || ch == 'W')
		{
			playerPos.x += sin(angleRad) * step;
			playerPos.y += cos(angleRad) * step;
		}

		if (ch == 's' || ch == 'S')
		{
			playerPos.x -= sin(angleRad) * step;
			playerPos.y -= cos(angleRad) * step;
		}

		if (ch == 'a' || ch == 'A')
		{
			playerPos.x -= cos(angleRad) * step;
			playerPos.y += sin(angleRad) * step;
		}

		if (ch == 'd' || ch == 'D')
		{
			playerPos.x += cos(angleRad) * step;
			playerPos.y -= sin(angleRad) * step;
		}

		if (ch == 'e' || ch == 'E')
		{
			playerTurn += turnStep;
		}

		if (ch == 'q' || ch == 'Q')
		{
			playerTurn -= turnStep;
		}

		if (ch == 27)
		{
			terminal_restore();
			return;
		}

		for (int i = scanStart; i < scanStop; i += scanStep)
		{
			float rad = (i + 180 + playerTurn) * 3.14159 / 180;
			float math_rad = rad + 3.14159/2;

			Object* hit;

			if (i % 45 == 0)
			{
				printf("|%d|", i);
			}
			if (raycastPoll((Ray){.origin = playerPos, .direction = {-cos(math_rad), sin(math_rad)}}, &objects, &hit))
			{
				printf("%c", abs(hit->id % 10) + '0');
			}
			else
			{
				printf(".");
			}
		}
		printf("\n\n");
	}
}

int main(void)
{
	cycle();

	return 0;
}

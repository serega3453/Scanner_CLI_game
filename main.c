#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>

#include "raycast.h"
#include "terminal.h"
#include "config.h"
#include "menu.h"
#include "saves.h"
#include "game.h"

void header_print(Vector2 pos, float playerTurn)
{
	char latDir = (pos.y >= 0) ? 'N' : 'S';
    char lonDir = (pos.x >= 0) ? 'E' : 'W';
    float lat = fabs(pos.y);
    float lon = fabs(pos.x);

	printf("GPS: %.2f%c %.2f%c\n", lat, latDir, lon, lonDir);

	float normalized = fmodf(playerTurn, 360.0f);
	if (normalized < 0) normalized += 360.0f;
	int headingIdx = (int)((normalized + 22.5f) / 45.0f) % 8;

	printf("HDG: %s\n\n", directions[headingIdx]);
}

void winning(IntArray* touched)
{
    printf("\n\nYOU WIN!!!\n");

    int lastBest = 0;

    FILE *fr = fopen("results.bin", "rb");
    if (fr != NULL) 
    {
        fread(&lastBest, sizeof(int), 1, fr);
        fclose(fr);
    }

    if (touched->count > lastBest) 
    {
        printf("\nNEW RECORD!!!\n%d objects touched!\nPrevious record: %d objects\n", touched->count, lastBest);
        
        FILE *fw = fopen("results.bin", "wb");
        if (fw != NULL) 
        {
            fwrite(&touched->count, sizeof(int), 1, fw);
            fclose(fw);
        }
    } 
    else 
    {
        printf("No new record(((\n%d objects touched\nPrevious record: %d objects\n", touched->count, lastBest);
    }

    printf("Press u to exit...\n");
    char ch = ' ';
    while (ch != 'u')
    	ch = terminal_getch();
    init();
}

void touchObject(ObjectArray* objects, IntArray* touched, Object* collision)
{
	for (int i = 0; i < touched->count; i++)
	{
		if (touched->items[i] == collision->id)
		{
			if ((collision->alive == false) && (killing_enabled == 1))
			{
				RemoveObjectById(objects, collision->id);
			}

			return;
		}
	}
	collision->alive = false;
	collision->color = RESET;

	addInt(touched, collision->id);

	if (killing_enabled == 1)
	{
		RemoveObjectById(objects, collision->id);
	}

	if (touched->count >= maxObjects)
	{
		winning(touched);
	}
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
		printf("%-15s%10s\n", "", "");
	}

	printf("\n%s%d%s%d%s\n", "Touched ", touched.count, " out of ", maxObjects, " objects");
}

void cycle(void)
{
	while(1)
	{
		if (renderMode == 1)
		{
			terminal_clear();
		}
		if (scanMode == 2)
		{
			scanStart = 90;
			scanStop = 270;
			scanStep = 1;
		}
		else
		{
			scanStart = 0;
			scanStop = 360;
			scanStep = 2;
		}

		simulation(&objects);

		header_print(playerPos, playerTurn);

		Object* collision = rendering(scanStart, scanStop, scanStep, playerTurn, playerPos, &objects);

		footer_print(step, turnStep, collision);

		float angleRad = playerTurn * 3.14159 / 180;

		int ch = terminal_getch();
		ch = tolower(ch);
		Vector2 nextPos = {playerPos.x, playerPos.y};

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
				nextPos.x += sin(angleRad) * step;
				nextPos.y += cos(angleRad) * step;
				if (!Pointcast(nextPos, &objects) && bounds(nextPos, (Vector2){mapX, mapY}))
				{
					playerPos = nextPos;
				}
				break;
			case 's':
				nextPos.x -= sin(angleRad) * step;
				nextPos.y -= cos(angleRad) * step;
				if (!Pointcast(nextPos, &objects) && bounds(nextPos, (Vector2){mapX, mapY}))
				{
					playerPos = nextPos;
				}
				break;
			case 'a':
				nextPos.x -= cos(angleRad) * step;
				nextPos.y += sin(angleRad) * step;
				if (!Pointcast(nextPos, &objects) && bounds(nextPos, (Vector2){mapX, mapY}))
				{
					playerPos = nextPos;
				}
				break;
			case 'd':
				nextPos.x += cos(angleRad) * step;
				nextPos.y -= sin(angleRad) * step;
				if (!Pointcast(nextPos, &objects) && bounds(nextPos, (Vector2){mapX, mapY}))
				{
					playerPos = nextPos;
				}
				break;
			case 'e':
				playerTurn += turnStep;
				break;
			case 'q':
				playerTurn -= turnStep;
				break;
			case 'z':
				if (collision != NULL)
				{
					touchObject(&objects, &touched, collision);
				}
				break;
			case ' ':
				break;
			case 27:
				menu();
				break;
		}
	}
}

int main(void)
{
	terminal_init();

	menu();

	cycle();

	return 0;
}

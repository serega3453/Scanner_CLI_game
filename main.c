#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "raycast.h"
#include "terminal.h"
#include <ctype.h>
#include <windows.h>

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
#define RESET "\033[37m"

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

int maxObjects = 150;	//SAVE

ObjectArray objects = {NULL, 0, 0};	//SAVE
IntArray touched = {NULL, 0, 0};	//SAVE

Vector2 playerPos = {0, 0};	//SAVE
float playerTurn = 180;	//SAVE
float step = 0.5;	//SAVE
float turnStep = 2;	//SAVE

int scanStart = 0;	//SAVE
int scanStop = 360;	//SAVE
int scanStep = 2;	//SAVE

int renderMode = 0;	//SAVE
int scanMode = 360;	//SAVE

float randRange(float min, float max)
{
	return min + (max - min) * ((float)rand() / RAND_MAX);
}

void header_print(float step)
{
	printf("Speed: %10.1f\n", step);
}

void touchObject(IntArray* touched, Object* collision)
{
	for (int i = 0; i < touched->count; i++)
	{
		if (touched->items[i] == collision->id)
		{
			return;
		}
	}
	collision->alive = false;
	addInt(touched, collision->id);
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
			if (hit->alive)
			{
				printf("%s%d\033[0m", colors[abs((hit->id * 7) % 10)], abs(hit->id % 10));
			}
			else
			{
				printf("%s%d\033[0m", RESET, abs(hit->id % 10));
			}

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

bool save_game(void) {
    FILE *f = fopen("save.bin", "wb");
    if (!f) return false;

    int settingsInt[6] = {
        maxObjects,
        scanStart,
        scanStop,
        scanStep,
        renderMode,
        scanMode
    };
    float settingsFloat[3] = {playerTurn, step, turnStep};

    fwrite(settingsInt, sizeof(int), 6, f);
    fwrite(settingsFloat, sizeof(float), 3, f);

    // 2. Глобальные переменные (сохраняем их напрямую)
    fwrite(&maxObjects, sizeof(int), 1, f);
    fwrite(&playerTurn, sizeof(float), 1, f);
    fwrite(&step, sizeof(float), 1, f);
    fwrite(&turnStep, sizeof(float), 1, f);
    fwrite(&scanStart, sizeof(int), 1, f);
    fwrite(&scanStop, sizeof(int), 1, f);
    fwrite(&scanStep, sizeof(int), 1, f);
    fwrite(&renderMode, sizeof(int), 1, f);
    fwrite(&scanMode, sizeof(int), 1, f);

    // 3. ObjectArray (сохраняем count + сами объекты)
    fwrite(&objects.count, sizeof(int), 1, f);
    if (objects.count > 0) {
        fwrite(objects.items, sizeof(Object), objects.count, f);
    }

    // 4. IntArray (сохраняем count + сами int'ы)
    fwrite(&touched.count, sizeof(int), 1, f);
    if (touched.count > 0) {
        fwrite(touched.items, sizeof(int), touched.count, f);
    }

    // 5. PlayerPos
    fwrite(&playerPos, sizeof(Vector2), 1, f);

    fclose(f);
    return true;
}

bool load_game(void) {
    FILE *f = fopen("save.bin", "rb");
    if (!f) return false;

    int settingsInt[6];
    float settingsFloat[3];
    
    fread(settingsInt, sizeof(int), 6, f);
    fread(settingsFloat, sizeof(float), 3, f);

    fread(&maxObjects, sizeof(int), 1, f);
    fread(&playerTurn, sizeof(float), 1, f);
    fread(&step, sizeof(float), 1, f);
    fread(&turnStep, sizeof(float), 1, f);
    fread(&scanStart, sizeof(int), 1, f);
    fread(&scanStop, sizeof(int), 1, f);
    fread(&scanStep, sizeof(int), 1, f);
    fread(&renderMode, sizeof(int), 1, f);
    fread(&scanMode, sizeof(int), 1, f);

    // 3. Загружаем ObjectArray
    int count;
    fread(&count, sizeof(int), 1, f);
    
    // Очищаем старые данные
    if (objects.items) free(objects.items);
    
    objects.count = count;
    objects.capacity = count;
    objects.items = malloc(sizeof(Object) * count);
    
    if (count > 0) {
        fread(objects.items, sizeof(Object), count, f);
    }

    // 4. Загружаем IntArray
    fread(&count, sizeof(int), 1, f);
    
    if (touched.items) free(touched.items);
    
    touched.count = count;
    touched.capacity = count;
    touched.items = malloc(sizeof(int) * count);
    
    if (count > 0) {
        fread(touched.items, sizeof(int), count, f);
    }

    // 5. PlayerPos
    fread(&playerPos, sizeof(Vector2), 1, f);

    fclose(f);
    return true;
}

void init(void)
{
	srand(time(NULL));

	if (touched.items) 
	{
    	free(touched.items);
    	touched.items = NULL;
    }

    touched.count = 0;
    touched.capacity = 0;

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

	for (int i = 0; i < maxObjects; i++)
	{
		addObject(&objects, (Object){.position = {randRange(-75, 75), randRange(-75, 75)}, .shape = circle, .signatureSize = randRange(1, 10), .id = i, .alive = true});
	}

    printf("GAME STARTED...");
}

void menu(void)
{
    char option;
    printf("\nSelect an option: \n");
    printf("0 - new game\n");
    printf("1 - load game\n");
    printf("2 - save game\n");
    printf("3 - settings");
    printf("q - exit\n");

    scanf(" %c", &option); 

    switch (option)
    {
    	case '0':
    		init();
    		break;
        case '1':
            load_game();
            break;
        case '2':
            save_game();
            break;
        case '3':
        	//settings_change();
        	break;
        case 'q':
        	exit(0);
            break;
    }
}

void cycle(void)
{
	printf("%f", objects.items[0].position.x);
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
			case 'z':
				if (collision != NULL)
				{
					touchObject(&touched, collision);
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

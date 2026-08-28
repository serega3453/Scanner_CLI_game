#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raycast.h"

#ifdef _WIN32
    #include <conio.h>
    #define GETCH() _getch()
#else
    #include <termios.h>
    #include <unistd.h>
    
    static struct termios old;
    
    void enableRaw() {
        tcgetattr(STDIN_FILENO, &old);
        struct termios new = old;
        new.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &new);
    }
    
    void disableRaw() {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &old);
    }
    
    int getch() {
        enableRaw();
        int ch = getchar();
        disableRaw();
        return ch;
    }
    
    #define GETCH() getch()
#endif

float randRange(float min, float max) {
    return min + (max - min) * ((float)rand() / RAND_MAX);
}

void cycle(void)
{
	srand(time(NULL));

	ObjectArray objects = {NULL, 0, 0};

	for (int i = 0; i < 10; i++)
	{
		addObject(&objects, (Object){.position = {randRange(-10, 10), randRange(-10, 10)}, .shape = circle, .signatureSize = randRange(1, 1), .id = i});
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

	while(1)
	{
		int ch = GETCH();
		if (renderMode == 1)
		{
			#ifdef _WIN32
            	system("cls");
        	#else
            	system("clear");
        	#endif
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
		
		if (ch == 27 || ch == 27)
		{
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
			else if (raycastPoll((Ray){.origin = playerPos, .direction = {-cos(math_rad), sin(math_rad)}}, &objects, &hit))
			{
				printf("%d", hit->id);
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
#include <stdlib.h>
#include "config.h"

const char* directions[8] =
{
	"N", "NE", "E", "SE", "S", "SW", "W", "NW"
};

const char* colors[11] = 
{
	RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN,
	BRIGHT_RED, BRIGHT_GREEN, BRIGHT_YELLOW, BRIGHT_BLUE, RESET
};

float mapX = 150;
float mapY = 150;
int maxObjects = 150;
int recordObjects = 0;
int killing_enabled = 0;
ObjectArray objects = {NULL, 0, 0};
IntArray touched = {NULL, 0, 0};
Vector2 playerPos = {0, 0};
float playerTurn = 0;
float step = 0.5;
float turnStep = 2;
int scanStart = 0, scanStop = 360, scanStep = 2;
int renderMode = 0, scanMode = 360;
float renderDistance = 50;
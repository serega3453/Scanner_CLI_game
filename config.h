#ifndef CONFIG_H
#define CONFIG_H
#include "structures.h"

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

extern const char* directions[8];
extern const char* colors[11];

extern float mapX, mapY;
extern int maxObjects, recordObjects, killing_enabled;
extern ObjectArray objects;
extern IntArray touched;
extern Vector2 playerPos;
extern float playerTurn, step, turnStep;
extern int scanStart, scanStop, scanStep;
extern int renderMode, scanMode;
extern float renderDistance;
#endif
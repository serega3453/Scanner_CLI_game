#include <stdio.h>
#include <stdlib.h>

#include "saves.h"
#include "config.h"

bool save_game() 
{
    FILE *f = fopen("save.bin", "wb");
    if (!f) return false;

    // 2. Глобальные переменные (сохраняем их напрямую)
    fwrite(&maxObjects, sizeof(int), 1, f);
    fwrite(&playerTurn, sizeof(float), 1, f);
    fwrite(&step, sizeof(float), 1, f);
    fwrite(&turnStep, sizeof(float), 1, f);
    fwrite(&mapX, sizeof(float), 1, f);
    fwrite(&mapY, sizeof(float), 1, f);
    fwrite(&scanStart, sizeof(int), 1, f);
    fwrite(&scanStop, sizeof(int), 1, f);
    fwrite(&scanStep, sizeof(int), 1, f);
    fwrite(&renderMode, sizeof(int), 1, f);
    fwrite(&scanMode, sizeof(int), 1, f);

    fwrite(&killing_enabled, sizeof(int), 1, f);

    fwrite(&renderDistance, sizeof(float), 1, f);

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

bool load_game() 
{
    FILE *f = fopen("save.bin", "rb");
    if (!f) return false;

    fread(&maxObjects, sizeof(int), 1, f);
    fread(&playerTurn, sizeof(float), 1, f);
    fread(&step, sizeof(float), 1, f);
    fread(&turnStep, sizeof(float), 1, f);
    fread(&mapX, sizeof(float), 1, f);
    fread(&mapY, sizeof(float), 1, f);
    fread(&scanStart, sizeof(int), 1, f);
    fread(&scanStop, sizeof(int), 1, f);
    fread(&scanStep, sizeof(int), 1, f);
    fread(&renderMode, sizeof(int), 1, f);
    fread(&scanMode, sizeof(int), 1, f);

    fread(&killing_enabled, sizeof(int), 1, f);

    fread(&renderDistance, sizeof(float), 1, f);

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
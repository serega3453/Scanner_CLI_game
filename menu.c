#include <stdio.h>

#include "menu.h"
#include "saves.h"
#include "game.h"
#include "config.h"

void settings()
{
    while(1)
    {
        char option;

        printf("\nSelect a setting: \n");
        printf("1 - Rendering mode\n");
        printf("2 - Scanning mode\n");
        printf("3 - Moving speed\n");
        printf("4 - Rendering distance\n");
        printf("5 - Turning speed\n");
        printf("6 - Killing mode\n");
        printf("q - Accept\n");

        scanf(" %c", &option); 

        switch (option)
        {
            case '1':
                printf("Current state: %d\n", renderMode);
                printf("1 - one line, 2 - not one line\n");
                scanf("%d", &renderMode);
                break;
            case '2':
                printf("Current state: %d\n", scanMode);
                printf("1 - 360 scan, 2 - 180 scan\n");
                scanf("%d", &scanMode);
                break;
            case '3':
                printf("Current state: %f\n", step);
                printf("Enter desired moving speed:\n");
                scanf("%f", &step);
                break;
            case '4':
                printf("Current state: %f\n", renderDistance);
                printf("Enter desired rendering distance:\n");
                scanf("%f", &renderDistance);
                break;
            case '5':
                printf("Current state: %f\n", turnStep);
                printf("Enter desired rotation speed:\n");
                scanf("%f", &turnStep);
                break;
            case '6':
                printf("Current state: %d\n", killing_enabled);
                printf("1 - enabled, 2 - disabled\n");
                scanf("%d", &killing_enabled);
                break;
            case 'q':
                return;
                break;
        }
    }
}

void menu()
{
    char option;
    printf("\nSelect an option: \n");
    printf("1 - new game\n");
    printf("2 - load game\n");
    printf("3 - save game\n");
    printf("4 - settings\n");
    printf("q - exit\n");

    scanf(" %c", &option); 

    switch (option)
    {
        case '1':
            init();
            break;
        case '2':
            load_game();
            break;
        case '3':
            save_game();
            break;
        case '4':
            settings();
            break;
        case 'q':
            exit(0);
            break;
    }
}
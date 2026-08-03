#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"
#include "init.h"
#include "character.h"
#include "game.h"
#include "combat.h"


int main()
{
    // Enabling ANSI sequence support in Windows
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
    srand(time(NULL));
    int choose;
    Character hero;
    Character enemy;
    Inventory database;

    init_game_database(&database);

    init_character(
        &enemy,             // ch
        "James_The_Enemy",  // name
        100.0,              // hp
        2,                  // weapon ID
        1,                  // helmet ID
        1,                  // breastplate ID
        1,                  // is_alive = true
        0                   // is_blocking = false
    );
    setup_character_loadout(
        &enemy,             // ch
        &database,          // pool of items
        2,                  // weapon ID
        1,                  // helmet ID 
        1,                  // breastplate ID 
        1,                  // small health potion count
        1,                  // medium health potion count
        0                   // large health potion count
    );

    printf("#############################################\n");
    printf("#           Welcome to the game!            #\n");
    printf("#############################################\n");
    printf("Choose action:\n[1]: Start game\n[2]: Exit\n");
    scanf("%d", &choose);
    switch(choose)
    {
        case 1:
            ClearScreen();
            choose_player_equipment(&hero, &database);
            ClearScreen();
            start_battle(&hero, &enemy, &database);
            break;
        case 2:
            exit(0);
        default:
            printf("Incorrect input!");
            WaitForKey();
            exit(0);
    }

	while (getchar() != '\n'); 
    getchar();
	return 0;
}
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "map.h"
#include "game.h"
#include "combat.h"
#include "character.h"

void print_dungeon(char dungeon[][MAP_WIDTH], int dungeon_fog[][MAP_WIDTH], Position hero_pos)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for(int j = 0; j < MAP_WIDTH; j++)
        {
            if (j == hero_pos.x && i == hero_pos.y) 
            {
                printf("@");
            }
            else if (dungeon_fog[i][j] == 1)
            {
                printf("%c", dungeon[i][j]);
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void fog_dissipation(int dungeon_fog[][MAP_WIDTH], Position hero_pos)
{
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            int target_x = hero_pos.x + dx;
            int target_y = hero_pos.y + dy;

            if (target_x >= 0 && target_x < MAP_WIDTH && target_y >= 0 && target_y < MAP_HEIGHT) 
            {
                dungeon_fog[target_y][target_x] = 1;
            }
        }
    }
}

int not_wall(char dungeon[][MAP_WIDTH], int x, int y)
{
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) return 0;
    return (dungeon[y][x] != '#') ? 1 : 0;
}

void start_floor_exploration(Character *player, const Inventory *database)
{
    char dungeon[MAP_HEIGHT][MAP_WIDTH] = 
    {
        {'#', '#', '#', '#', '#', '#', '#'},
        {'#', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '#', '#', '#'},
        {'#', '.', '#', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '#', 'B', '#'},
        {'#', '#', '#', '#', '#', '#', '#'}
    };

    int dungeon_fog[MAP_HEIGHT][MAP_WIDTH] = 
    {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}
    };

    Position hero_pos = {3, 3};

    Position boss_pos = {5, 5};

    char move;
    int exploring = 1;
    while (exploring && player->is_alive)
    {
        fog_dissipation(dungeon_fog, hero_pos);
        ClearScreen();
        printf("=== DUNGEON FLOOR ===\n\n");
        print_dungeon(dungeon, dungeon_fog, hero_pos);
        printf("Select the direction of movement:\n");
        printf("[W]: Up\n[A]: Left\n[D]: Right\n[S]: Down\n");
        scanf(" %c", &move);
        while(getchar() != '\n');
        switch(move)
        {
            case 'w': case 'W':
                if(not_wall(dungeon, hero_pos.x, hero_pos.y - 1))
                {
                    hero_pos.y -= 1;
                }
                break;
            case 'a': case 'A':
                if(not_wall(dungeon, hero_pos.x - 1, hero_pos.y))
                {
                    hero_pos.x -= 1;
                }
                break;
            case 'd': case 'D':
                if(not_wall(dungeon, hero_pos.x + 1, hero_pos.y))
                {
                    hero_pos.x += 1;
                }
                break;
            case 's': case 'S':
                if(not_wall(dungeon, hero_pos.x, hero_pos.y + 1))
                {
                    hero_pos.y += 1;
                }
                break;
        }

        if (hero_pos.x == boss_pos.x && hero_pos.y == boss_pos.y)
        {
            Character boss;
            init_character(
                &boss,             // ch
                "BOSS",             // name
                150.0,              // hp
                150.0,              // max_hp
                2,                  // weapon ID
                2,                  // helmet ID
                2,                  // breastplate ID
                1,                  // is_alive = true
                0                   // is_blocking = false
            );
            setup_character_loadout(
                &boss,             // ch
                database,          // pool of items
                2,                  // weapon ID
                2,                  // helmet ID 
                2,                  // breastplate ID 
                1,                  // small health potion count
                1,                  // medium health potion count
                1                   // large health potion count
            );
            ClearScreen();
            printf("You have come face-to-face with the dungeon BOSS!\n");
            WaitForKey();
            ClearScreen();
            start_battle(player, &boss, database);

            if (player->is_alive) {
                printf("\nYOU BEAT THE GAME! The Boss is dead!\n");
                exploring = 0;
            } else {
                exploring = 0;
            }
            WaitForKey();
        }
        else if (move)
        {
            int encounter_roll = rand() % 100;

            if (encounter_roll < 25) // 25%
            {
                ClearScreen();
                printf("Danger! An enemy jumps out of the shadows!\n");
                WaitForKey();

                Character monster;
                int random_hp = 50 + rand() % (100 - 50 + 1);
                int random_weapon = rand() % 4;
                int random_helmet = rand() % 3;
                int random_breastplate = rand() % 3;

                init_character(
                    &monster,           // ch
                    "Monster",          // name
                    random_hp,          // hp
                    random_hp,          // max_hp
                    random_weapon,      // weapon ID
                    random_helmet,      // helmet ID
                    random_breastplate, // breastplate ID
                    1,                  // is_alive = true
                    0                   // is_blocking = false
                );
                setup_character_loadout(
                    &monster,           // ch
                    database,          // pool of items
                    random_weapon,      // weapon ID
                    random_helmet,      // helmet ID 
                    random_breastplate, // breastplate ID 
                    1,                  // small health potion count
                    0,                  // medium health potion count
                    0                   // large health potion count
                );
                start_battle(player, &monster, database);

                if (!player->is_alive)
                {
                    exploring = 0;
                    continue;
                }

                ClearScreen();
                printf("You defeated the Monster and cleared the room!\n");
                WaitForKey();
            }
        }
    }
    return;
}
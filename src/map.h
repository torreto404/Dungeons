#ifndef MAP_H
#define MAP_H

#include "types.h"

#define MAP_HEIGHT 7
#define MAP_WIDTH 7

void start_floor_exploration(Character *player, const Inventory *database);
void fog_dissipation(int dungeon_fog[][MAP_WIDTH], Position hero_pos);
void print_dungeon(char dungeon[][MAP_WIDTH], int dungeon_fog[][MAP_WIDTH], Position hero_pos);
int not_wall(char dungeon[][MAP_WIDTH], int x, int y);

#endif
#ifndef INIT_H
#define INIT_H

#include "types.h"

void init_game_database(Inventory *inv);
void add_weapon(Inventory *inv, Weapon weapon);
void add_breastplate(Inventory *inv, Breastplate breastplate);
void add_helmet(Inventory *inv, Helmet helmet);
void add_health_potion(Inventory *inv, Health_potion health_potion);

#endif
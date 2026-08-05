#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

void init_character(Character *ch, char * name, float hp, float max_hp, int id_weapon, int id_helmet, int id_breastplate, int is_alive, int is_blocking);

void setup_character_loadout(Character *ch, const Inventory *database, int id_weapon, int id_helmet, int id_breastplate, int small_p_qty, int med_p_qty, int large_p_qty);

#endif
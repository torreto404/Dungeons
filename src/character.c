#include "character.h"
#include "init.h"
#include <string.h>

void init_character(Character *ch, char * name, float hp, int id_weapon, int id_helmet, int id_breastplate, int is_alive, int is_blocking)
{
    strncpy(ch->name, name, 19);
    ch->name[19] = '\0';
    ch->hp = hp;
    ch->max_hp = 100.0;
    ch->level = 10;
    ch->is_alive = is_alive;
    ch->is_blocking = is_blocking;

    ch->id_weapon = id_weapon;
    ch->id_helmet = id_helmet;
    ch->id_breastplate = id_breastplate;

    ch->backpack.count_weapon = 0;
    ch->backpack.count_helmet = 0;
    ch->backpack.count_breastplate = 0;
    ch->backpack.count_health_potion = 0;
}

void setup_character_loadout(Character *ch, const Inventory *database, int id_weapon,  
    int id_helmet, int id_breastplate, int small_p_qty, int med_p_qty, int large_p_qty)
{
    add_weapon(&ch->backpack, database->items_weapon[id_weapon]);
    add_weapon(&ch->backpack, database->items_weapon[3]);   // default fists
    add_helmet(&ch->backpack, database->items_helmet[id_helmet]); 
    add_breastplate(&ch->backpack, database->items_breastplate[id_breastplate]);
    
    if (small_p_qty > 0)
    {
        Health_potion small_p = database->items_health_potion[0];
        small_p.quantity = small_p_qty; 
        add_health_potion(&ch->backpack, small_p);
    }
    if (med_p_qty > 0)
    {
        Health_potion medium_p = database->items_health_potion[1];
        medium_p.quantity = med_p_qty; 
        add_health_potion(&ch->backpack, medium_p);
    }
    if (large_p_qty > 0)
    {
        Health_potion large_p = database->items_health_potion[2];
        large_p.quantity = large_p_qty; 
        add_health_potion(&ch->backpack, large_p);
    }
}
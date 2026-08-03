#include <stdio.h>
#include <string.h>

#include "init.h"
#include "types.h"

void add_weapon(Inventory *inv, Weapon weapon)
{
    if (inv->count_weapon < 5) {
        inv->items_weapon[inv->count_weapon] = weapon;
        inv->count_weapon++;
    } else {
        printf("Weapon inventory is full!\n");
    }
}

void add_breastplate(Inventory *inv, Breastplate breastplate)
{
    if (inv->count_breastplate < 5) {
        inv->items_breastplate[inv->count_breastplate] = breastplate;
        inv->count_breastplate++;
    } else {
        printf("Breastplate inventory is full!\n");
    }
}

void add_helmet(Inventory *inv, Helmet helmet)
{
    if (inv->count_helmet < 5) {
        inv->items_helmet[inv->count_helmet] = helmet;
        inv->count_helmet++;
    } else {
        printf("Helmet inventory is full!\n");
    }
}

void add_health_potion(Inventory *inv, Health_potion health_potion)
{
    for (int i = 0; i < inv->count_health_potion; i++)
    {
        if (inv->items_health_potion[i].id == health_potion.id)
        {
            inv->items_health_potion[i].quantity += health_potion.quantity;
            return;
        }
    }
    if (inv->count_health_potion < 5) {
        inv->items_health_potion[inv->count_health_potion] = health_potion;
        inv->count_health_potion++;
    } else {
        printf("Potion inventory is full! Cannot add a new type of potion.\n");
    }
}

void init_game_database(Inventory *inv)
{
	inv->count_helmet = 0;
    inv->count_breastplate = 0;
    inv->count_weapon = 0;
    inv->count_health_potion = 0;

    // --- Weapons ---
    Weapon sword = {0, "", 10};
    strncpy(sword.name, "Sword", 19);
    add_weapon(inv, sword);
    
    Weapon axe = {1, "", 12};
    strncpy(axe.name, "Axe", 19);
    add_weapon(inv, axe);

    Weapon bow = {2, "", 8};
    strncpy(bow.name, "Bow", 19);
    add_weapon(inv, bow);

    Weapon fists = {3, "", 2};
    strncpy(fists.name, "Fists", 19);
    add_weapon(inv, fists);

    // --- Breastplates ---
    Breastplate miss_b = {0, "", 0.0};
    strncpy(miss_b.name, "Missing_breastplate", 19);
    add_breastplate(inv, miss_b);

    Breastplate leather_b = {1, "", 0.15};
    strncpy(leather_b.name, "Leather_breastplate", 19);
    add_breastplate(inv, leather_b);

    Breastplate iron_b = {2, "", 0.3};
    strncpy(iron_b.name, "Iron_breastplate", 19);
    add_breastplate(inv, iron_b);

    // --- Helmets ---
    Helmet miss_h = {0, "", 0.0};
    strncpy(miss_h.name, "Missing_helmet", 19);
    add_helmet(inv, miss_h);

    Helmet leather_h = {1, "", 0.1};
    strncpy(leather_h.name, "Leather_helmet", 19);
    add_helmet(inv, leather_h);

    Helmet iron_h = {2, "", 0.2};
    strncpy(iron_h.name, "Iron_helmet", 19);
    add_helmet(inv, iron_h);

    // --- Health potions ---
    Health_potion small_p = {0, "", 10.0, 0};
    strncpy(small_p.name, "small_health_potion", 19);
    add_health_potion(inv, small_p);

    Health_potion med_p = {1, "", 25.0, 0};
    strncpy(med_p.name, "medium_health_potion", 19);
    add_health_potion(inv, med_p);

    Health_potion large_p = {2, "", 50.0, 0};
    strncpy(large_p.name, "large_health_potion", 19);
    add_health_potion(inv, large_p);
}
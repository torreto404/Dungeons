#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "types.h"
#include "init.h"
#include "game.h"
#include "character.h"

void ClearScreen(void)
{
    printf("\033[H\033[J"); // ANSI
    fflush(stdout);
}

void WaitForKey(void) {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
}

int menu_choose_helmet(const Inventory *database)
{
    ClearScreen();
    printf("=== Choose helmet ===\n");
    for(int i = 0; i < database->count_helmet; i++)
    {
        printf("[%d]: %s - %.1f%% defence\n", i+1, database->items_helmet[i].name, database->items_helmet[i].defence * 100);
    }
    int choice;
    printf("Enter id of helmet: \n");
    scanf("%d", &choice);

    if (choice > 0 && choice <= database->count_helmet)
    {
        return choice-1;
    }
    else
    {
        printf("Incorrect ID!\n");
        return 0;
    }
}

int menu_choose_breastplate(const Inventory *database)
{
    ClearScreen();
    printf("=== Choose breastplate ===\n");
    for(int i = 0; i < database->count_breastplate; i++)
    {
        printf("[%d]: %s - %.1f%% defence\n", i+1, database->items_breastplate[i].name, database->items_breastplate[i].defence * 100);
    }
    int choice;
    printf("Enter id of breastplate: \n");
    scanf("%d", &choice);

    if (choice > 0 && choice <= database->count_breastplate)
    {
        return choice-1;
    }
    else
    {
        printf("Incorrect ID!\n");
        return 0;
    }
}

int menu_choose_weapon(const Inventory *database)
{
    ClearScreen();
    printf("=== Choose weapon ===\n");
    for(int i = 0; i < database->count_weapon; i++)
    {
        printf("[%d]: %s - %d damage\n", i+1, database->items_weapon[i].name, database->items_weapon[i].damage);
    }
    int choice;
    printf("Enter id of weapon: \n");
    scanf("%d", &choice);

    if (choice > 0 && choice <= database->count_weapon)
    {
        return choice-1;
    }
    else
    {
        printf("Incorrect ID!\n");
        return 0;
    }
}

void choose_player_equipment(Character *player, const Inventory *database)
{
    char name[20];
    int choose;
    int sub_choose;
    int is_customizing = 1;
    printf("Enter name of your character: ");
    scanf("%19s", name);
    ClearScreen();
    printf("Welcome %s!\n", name);
    printf("Do you want to customize your character?\n");
    printf("[1]: Yes\n[2]: No (Standard equipment will be used!)\n"); // Standard: Helmet - Leather; Breastplate - Iron; Weapon - sword; Health potion - 3 small, 2 medium, 1 large; 
    scanf("%d", &choose);
    int selected_weapon = -1;
    int selected_helmet = -1;
    int selected_breastplate = -1;
    switch (choose)
    {
        case 1:
            while(is_customizing)
            {
                ClearScreen();
                if (selected_helmet != -1)
                {
                    printf("Current helmet - %s\n", database->items_helmet[selected_helmet].name);
                }
                if (selected_breastplate != -1)
                {
                    printf("Current breastplate - %s\n", database->items_breastplate[selected_breastplate].name);
                }
                if (selected_weapon != -1)
                {
                    printf("Current weapon - %s\n", database->items_weapon[selected_weapon].name);
                }
                printf("Choose equipment for your hero:\n");
                printf("[1]: Helmet\n[2]: Breastplate\n[3]: Weapon\n[4]: Finish character customization\n");
                scanf("%d", &sub_choose);
                switch(sub_choose)
                {
                    case 1:
                        ClearScreen();
                        selected_helmet = menu_choose_helmet(database);
                        break;
                    case 2:
                        ClearScreen();
                        selected_breastplate = menu_choose_breastplate(database);
                        break;
                    case 3:
                        ClearScreen();
                        selected_weapon = menu_choose_weapon(database);
                        break;
                    case 4:
                        if (selected_helmet != -1 && selected_breastplate != -1 && selected_weapon != -1)
                        {
                            init_character(
                                player,                 // ch
                                name,                   // name
                                100.0,                  // hp
                                selected_weapon,        // weapon ID
                                selected_helmet,        // helmet ID
                                selected_breastplate,   // breastplate ID
                                1,                      // is_alive = true
                                0                       // is_blocking = false
                            );
                            setup_character_loadout(
                                player,                 // ch
                                database,               // pool of items
                                selected_weapon,        // weapon ID
                                selected_helmet,        // helmet ID
                                selected_breastplate,   // breastplate ID
                                3,                      // small health potion count
                                2,                      // medium health potion count
                                1                       // large health potion count
                            );
                            is_customizing = 0;
                            break;
                        }
                }
            }
            break;
        case 2:
            init_character(
                player,     // ch
                name,       // name
                100.0,      // hp
                0,          // weapon ID
                1,          // helmet ID
                2,          // breastplate ID
                1,          // is_alive = true
                0           // is_blocking = false
            );
            setup_character_loadout(
                player,     // ch
                database,   // pool of items
                0,          // weapon ID
                1,          // helmet ID
                2,          // breastplate ID
                3,          // small health potion count
                2,          // medium health potion count
                1           // large health potion count
            );
            break;
        default:
            printf("Incorrect input!");
            exit(0);
    }
}

void show_character(const Character *ch, const Inventory *database)
{
    printf("\n---=== %s ===---\n", ch->name);
    printf("HP: %.1f/%.1f\n", ch->hp, ch->max_hp);
    printf("Level: %d\n", ch->level);
    printf("Weapon: %s\n", database->items_weapon[ch->id_weapon].name);
    printf("Helmet: %s\n", database->items_helmet[ch->id_helmet].name);
    printf("Breastplate: %s\n", database->items_breastplate[ch->id_breastplate].name);
    printf("Backpack: %d potions\n", 
           ch->backpack.count_health_potion);
}

void damage_character(Character *ch, int damage, float defence)
{
    ClearScreen();
    if (ch == NULL) {
        printf("Error: Character is NULL!\n");
        return;
    }
    if (defence > 1.0) defence = 1.0;
    if (defence < 0) defence = 0;
    float true_damage = damage - (damage * defence);
    if (damage < 0)
    {
        printf("Damage cannot be negative!\n");
        return;
    }
    ch->hp -= true_damage;
    if (ch->hp < 0)
    {
        ch->hp = 0;
    }

    printf("%s took %d damage (%.1f after defence)! HP: %.1f/%.1f\n", 
           ch->name, damage, true_damage, ch->hp, ch->max_hp);
    
    if (ch->hp <= 0) {
        ch->is_alive = 0;
        printf("💀 %s has been defeated! 💀\n", ch->name);
    }
    WaitForKey();
}

void heal(Character *ch)
{
    float heal = 0.0;
    if (ch->hp <= 0 )
    {
        printf("%s is dead! Cannot heal!\n", ch->name);
        return;
    }
    if (ch->hp >= ch->max_hp) {
        printf("%s already has full health!\n", ch->name);
        return;
    }
    if (heal < 0)
    {
        printf("Heal cannot be negative!\n");
        return;
    }

    if (ch->hp <=50)
    {
        for (int i = ch->backpack.count_health_potion - 1; i >= 0 ; i--)
        {
            if (ch->backpack.items_health_potion[i].quantity > 0)
            {
                heal = ch->backpack.items_health_potion[i].heal;
                break;
            }
        }
    }

    ch->hp += heal;
    if (ch->hp > ch->max_hp)
    {
        ch->hp = ch->max_hp;
    }
    printf("%s restore hp: %f\n", ch->name, heal);
}

void attack_character(Character *attacker, Character *defender)
{
    float damage = 0.0;
    float defence = 0.0;
    int found_weapon = 0;

    // searching for a helmet in the defender's inventory
    for (int i = 0; i < defender->backpack.count_helmet; i++)
    {
        if (defender->id_helmet == defender->backpack.items_helmet[i].id)
        {
            defence += defender->backpack.items_helmet[i].defence;
            break;
        }
    }

    // searching for a breastplate in the defender's inventory
    for (int i = 0; i < defender->backpack.count_breastplate; i++)
    {
        if (defender->id_breastplate == defender->backpack.items_breastplate[i].id)
        {
            defence += defender->backpack.items_breastplate[i].defence;
            break;
        }
    }

    // searching for a weapon in the attacker's inventory
    for (int i = 0; i < attacker->backpack.count_weapon; i++)
    {
        if (attacker->id_weapon == attacker->backpack.items_weapon[i].id)
        {
            damage = attacker->backpack.items_weapon[i].damage;
            found_weapon = 1;
            break;
        }
    }
    
    if (found_weapon == 0)
    {
        for (int i = 0; i < attacker->backpack.count_weapon; i++)
        {
            if (strcmp(attacker->backpack.items_weapon[i].name, "Fists") == 0)
            {
                damage = attacker->backpack.items_weapon[i].damage;
                break;
            }
        }
    }

    if (defender->is_blocking == 1)
    {
        int roll = rand() % 100;
        int block_chance = 65;   // 65% - block probability
        
        if (roll < block_chance)
        {
            damage = damage * 0.5f; 
            printf("🛡️ %s successfully BLOCKED the attack! Damage halved!\n", defender->name);
        }
        else
        {
            printf("❌ %s tried to block, but FAILED! Taking full damage!\n", defender->name);
        }
    }

    damage_character(defender, damage, defence);
}

void use_health_potion(Character *player)
{
    
}
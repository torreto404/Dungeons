#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "game.h"


void enemy_ai_turn(Character *enemy, Character *hero)
{
    int enemy_damage = 0;
    int roll = 0;

    for (int i = 0; i < enemy->backpack.count_weapon; i++) 
    {
        if (enemy->id_weapon == enemy->backpack.items_weapon[i].id) 
        {
            enemy_damage = enemy->backpack.items_weapon[i].damage;
            break;
        }
    }

    if(hero->hp * 1.25 <= enemy_damage) // finishing off
    {
        printf("The %s deals you a fatal blow.\n", enemy->name);
        attack_character(enemy, hero);
        return;
    }

    if (enemy->hp <= 50 && enemy->backpack.count_health_potion > 0)
    {
        int found_index = -1;
        for (int i = enemy->backpack.count_health_potion - 1; i >= 0 ; i--)
        {
             if (enemy->backpack.items_health_potion[i].quantity > 0)
            {
                found_index = i;
                break;
            }
        }
        if (found_index != -1)
        {
            enemy->hp += enemy->backpack.items_health_potion[found_index].heal;
            
            if (enemy->hp > enemy->max_hp)
            {
                enemy->hp = enemy->max_hp;
            }

            printf("The %s used a %s and restored %1.f health.\nNow his health is %.1f.\n", 
                enemy->name, 
                enemy->backpack.items_health_potion[found_index].name, 
                enemy->backpack.items_health_potion[found_index].heal,
                enemy->hp
            );

            enemy->backpack.items_health_potion[found_index].quantity--;

            return;
        }
    }

    if(hero->is_blocking)
    {
        attack_character(enemy, hero);
        return;
    }
    
    roll = rand() % 100;

    if(roll < 70)   // 70% to attack
    {
        printf("The %s attacks you!\n", enemy->name);
        attack_character(enemy, hero);
        return;
    }
    else            // 30% to block 
    {
        printf("%s raised his shield and prepared to block!\n", enemy->name);
        enemy->is_blocking = 1;
        return;
    }
}
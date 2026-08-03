#ifndef GAME_H
#define GAME_H

void attack_character(Character *attacker, Character *defender);
void heal(Character *ch);
void damage_character(Character *ch, int damage, float defence);
void show_character(const Character *ch, const Inventory *database);
void choose_player_equipment(Character *player, const Inventory *database);
void ClearScreen(void);
void WaitForKey(void);
int menu_choose_helmet(const Inventory *database);
int menu_choose_breastplate(const Inventory *database);
int menu_choose_weapon(const Inventory *database);
void use_health_potion(Character *player);


#endif
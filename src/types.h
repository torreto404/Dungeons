#ifndef TYPES_H
#define TYPES_H

typedef struct
{
	int id;
	char name[20];
	int damage;
} Weapon;

typedef struct
{
	int id;
	char name[20];
	float defence;
} Helmet;

typedef struct
{
	int id;
	char name[20];
	float defence;
} Breastplate;

typedef struct
{
	int id;
	char name[20];
	float heal;
	int quantity;
} Health_potion;

typedef struct
{
	Weapon items_weapon[5];
	Helmet items_helmet[5];
	Breastplate items_breastplate[5];
	Health_potion items_health_potion[5];
	int count_helmet, count_breastplate, count_weapon, count_health_potion;
} Inventory;

typedef struct
{
	char name[20];
	float hp;
	float max_hp;
	int id_weapon;
	int id_helmet;
	int id_breastplate;
	int id_health_potion;
	int level;
	int is_alive;
	int is_blocking;

	Inventory backpack;
} Character;

#endif
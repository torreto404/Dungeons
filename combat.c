#include <stdio.h>
#include <stdlib.h>

#include "combat.h"
#include "game.h"

void print_turn(int turn)
{
	ClearScreen();
	printf("############################################\n");
    printf("#               Turn:	#%d                #\n", turn);
    printf("############################################\n");
}

void start_battle(Character *player, Character *enemy, Inventory *database)
{
	int turn = 0;
	int choose;
	printf("##############################################\n");
    printf("#               Start battle!               #\n");
    printf("##############################################\n");
	WaitForKey();
	while(player->is_alive && enemy->is_alive)
	{
		print_turn(turn);
		show_character(player, database);
		show_character(enemy, database);
		printf("---------------------------------------\n");
		printf("Choose action:\n[1]: Attack\n[2]: Block\n[3]: Use a healing potion\n");
		scanf("%d", &choose);
		while (getchar() != '\n'); 
		switch(choose)
		{
			case 1:
				attack_character(player, enemy);
				WaitForKey();
				break;
			case 2:
				player->is_blocking = 1;
				printf("🛡️ You raised your shield and prepared to block!\n");
				WaitForKey();
				break;
			case 3:
				use_health_potion(player);
				WaitForKey();
				break;
			default:
				printf("Incorrect input!");
				WaitForKey();
				exit(0);
		}
	
		turn++;
	}
	return;
}
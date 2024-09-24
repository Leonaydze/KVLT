#include "Altar.h"

void Altar::RegeneratePlayerHealth(Player &player){
	if (player.GetPlayerHealth() <= 0 or player.GetPlayerHealth() != 100) {
		player.HealPlayer(100 - player.GetPlayerHealth());
	}
}

Altar::Altar(){

}



#include "PlayerInventory.h"

void PlayerInventory::HealFlask(Player &player, Flask flask){
	if (_currentCountFlax >= 1) {
		player.HealPlayer(flask.GetMaxHealCount());
		_currentCountFlax--;
	}
}

PlayerInventory::PlayerInventory(){
	_currentCountFlax = 1;
}


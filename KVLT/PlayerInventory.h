#pragma once
#include "Flask.h"
#include "Player.h"

class PlayerInventory{
private:
	int _currentCountFlax = 0;
	int _maxCountFlax = 5;
	
	void HealFlask(Player &player, Flask flask);
public:
	PlayerInventory();
};


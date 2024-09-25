#pragma once
#include "Flask.h"
#include "Player.h"

class PlayerInventory{
private:
	unsigned short int _currentCountFlax = 0;
	unsigned short int _maxCountFlax = 5;
	
	void HealFlask(Player &player, Flask flask);
public:
	PlayerInventory();

	int GetCurrentCountFlask();
};


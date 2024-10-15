#pragma once
#include "Flask.h"
#include "Player.h"
#include "PlayerWeapon.h"

class PlayerInventory{
private:
	unsigned short int _currentCountFlask = 0;
	unsigned short int _maxCountFlask = 5;
	
	void HealFlask(Player &player, Flask flask);
public:
	int id = -1;
	PlayerInventory();

	PlayerInventory(int currentCountFlask) : _currentCountFlask(currentCountFlask) {}

	PlayerInventory(int id, const PlayerInventory& other) : _currentCountFlask(other._currentCountFlask) {}

	int GetCurrentCountFlask();

	json toJson() const;
	static PlayerInventory fromJson(const json& _filename);
};


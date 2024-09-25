#pragma once
#include "Flask.h"
#include "Player.h"

class PlayerInventory{
private:
	unsigned short int _currentCountFlax = 0;
	unsigned short int _maxCountFlax = 5;
	
	void HealFlask(Player &player, Flask flask);

	const std::string _filename = "pInvData.json";
public:
	PlayerInventory();

	int GetCurrentCountFlask();

	void CreateData();
	void ReadData();
	void UpdateData(unsigned short int index);
	void RemoveData(unsigned short int index);
};


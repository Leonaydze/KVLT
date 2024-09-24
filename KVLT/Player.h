#pragma once

class Player{
private:
	int _playerHealth = 100;
public:
	int GetPlayerHealth();
	void HealPlayer(int healthAmount);
};


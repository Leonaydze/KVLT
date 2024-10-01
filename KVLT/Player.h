#pragma once
#include <raylib.h>

class Player{
private:
	short int _playerHealth = 100;

	Vector2 _playerPosition = { 0, 0 };
public:
	Player();

	int GetPlayerHealth();
	void HealPlayer(int healthAmount);

	Vector2 GetPlayerPositionV();
	void SetPlayerPositionV(Vector2 playerPosition);

	float GetPlayerPositionX();
	void SetPlayerPositionX(float playerPosX);

	float GetPlayerPositionY();
	void SetPlayerPositionY(float playerPosY);
};


#pragma once
#include <raylib.h>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class Player{
private:
	short int _playerHealth = 100;

	Vector2 _playerPosition = { 0, 0 };
public:
	Player(short int _playerHealth, double _playerPosX, double _playerPosY) {
	};

	int GetPlayerHealth();
	void HealPlayer(int healthAmount);

	Vector2 GetPlayerPositionV();
	void SetPlayerPositionV(Vector2 playerPosition);

	float GetPlayerPositionX();
	void SetPlayerPositionX(float playerPosX);

	float GetPlayerPositionY();
	void SetPlayerPositionY(float playerPosY);

	json toJson() const;
	Player fromJson(const json& _filename);
};


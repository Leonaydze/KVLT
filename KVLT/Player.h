#pragma once
#include <raylib.h>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;


class Player{
private:
	const std::string _filename = "playerData.json";
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

	void CreateData();
	void ReadData();
	void UpdateData(unsigned short int index);
	void RemoveData(unsigned short int index);
};


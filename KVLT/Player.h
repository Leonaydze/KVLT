#pragma once
#include <raylib.h>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class Player{
private:
	short int _playerHealth = 100;

	Vector2 _playerPosition = { 10, -100 };

	Vector2 _playerVelocity{ 0.0f, 0.0f };

	float _playerSpeed = 5.0f;

	float _jumpHeight = 0;
	float _jumpMaxHeight = 200;
	float _playerJumpSpeed = 6.5f;

	bool _playerCanJump = true;
	bool _playerJump = false;
	bool _playerCanWalk = true;
public:
	int id = -1;
	Player() {};
	Player(short int _playerHealth, double _playerPosX, double _playerPosY) {
		this->_playerHealth = _playerHealth;
		this->_playerPosition.x = _playerPosX;
		this->_playerPosition.y = _playerPosY;
	};

	Player(int id, const Player& other) : _playerHealth(other._playerHealth), _playerPosition(other._playerPosition) {}

	int GetPlayerHealth();
	void HealPlayer(int healthAmount);

	Vector2 GetPlayerPositionV();
	void SetPlayerPositionV(Vector2 playerPosition);

	float GetPlayerPositionX();
	void SetPlayerPositionX(float playerPosX);

	float GetPlayerPositionY();
	void SetPlayerPositionY(float playerPosY);

	json toJson() const;
	static Player fromJson(const json& _filename);

	void PlayerController();

	bool IsPlayerJump();
	float GetJumpHeight();
	bool PlayerMaxJump();
	void SetPlayerCanJump(bool playerCanJump);
	bool GetPlayerCanJump();

	void MoveVertically();
	void MoveVerticallyDown();
};


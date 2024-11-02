#pragma once
#include <raylib.h>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class Player{
private:
	unsigned short int _maxPlayerHealth = 100;
	short int _playerHealth = _maxPlayerHealth;

	Vector2 _playerPosition = { 0, 870 };

	Vector2 _playerVelocity = { 0.0f, 0.0f };

	float _playerSpeed = 4.0f;

	float _jumpHeight = 0;
	float _jumpMaxHeight = 200;
	float _playerJumpSpeed = 6.5f;

	bool _playerCanJump = true;
	bool _playerJump = false;
	int _playerCanWalk = 0;

	Texture2D _playerTexture = LoadTexture("");
	Rectangle _frameRec{0, 131, 131, 131};

	int currentFrame = 0;

	int framesCounter = 0;
	int framesSpeed = 8;

	unsigned short int _maxStamina = 4;
	unsigned short int _stamina = _maxStamina;

	float _lastUpdateTime = 0;
	bool TriggerEvent(float interval);

	Sound _dash = LoadSound("");
public:
	Sound _jump = LoadSound("");

	int id = -1;

	Player() {};
	Player(int id, short int _playerHealth, float _playerPosX, float _playerPosY) {
		this->_playerHealth = _playerHealth;
		this->_playerPosition.x = _playerPosX;
		this->_playerPosition.y = _playerPosY;
		this->id = id;
	};

	Player(int id, const Player& other) : _playerHealth(other._playerHealth), _playerPosition(other._playerPosition) {}

	short int GetPlayerHealth();
	void SetPlayerHealth(short int playerHealth);
	unsigned short int GetMaxPlayerHealth();
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

	/// <summary>
	/// The player can walk in directions
	/// </summary>
	/// <param name="playerCanWalk"> -1 -- left, 0 -- all directions, 1 -- right</param>
	void SetPlayerCanWalk(int playerCanWalk);

	bool IsPlayerJump();
	float GetJumpHeight();
	bool PlayerMaxJump();
	void SetPlayerCanJump(bool playerCanJump);
	bool GetPlayerCanJump();

	void MoveVertically();
	void MoveVerticallyDown();

	void Init(/*Player player*/);
	void Draw();

	bool PlayerDeath();
};


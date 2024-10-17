#include "Player.h"

int Player::GetPlayerHealth(){
	return _playerHealth;
}

void Player::HealPlayer(int healthAmount){
	_playerHealth += healthAmount;
	if (_playerHealth >= 100) {
		_playerHealth = 100;
	}
}

Vector2 Player::GetPlayerPositionV(){
	return _playerPosition;
}

void Player::SetPlayerPositionV(Vector2 playerPosition){
	_playerPosition = playerPosition;
}

float Player::GetPlayerPositionX(){
	return _playerPosition.x;
}

void Player::SetPlayerPositionX(float playerPosX){
	_playerPosition.x = playerPosX;
}

float Player::GetPlayerPositionY(){
	return _playerPosition.y;
}

void Player::SetPlayerPositionY(float playerPosY){
	_playerPosition.y = playerPosY;
}

json Player::toJson() const
{
	return json{ {"id", id}, { "Health", _playerHealth }, {"PosX", _playerPosition.x}, {"PosY", _playerPosition.y}};
}

Player Player::fromJson(const json& _filename)
{
	return Player(_filename["Health"], _filename["PosX"], _filename["PosY"]);
}

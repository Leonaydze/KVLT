#include "Player.h"

Player::Player(short int _playerHealth, double _playerPosX, double _playerPosY) {
	this->_playerHealth = _playerHealth;
	this->_playerPosition.x = _playerPosX;
	this->_playerPosition.y = _playerPosY;
}

int Player::GetPlayerHealth(){
	return _playerHealth;
}

void Player::HealPlayer(int healthAmount){
	_playerHealth += healthAmount;
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
	return json{ {"Health", _playerHealth}, {"PosX", _playerPosition.x}, {"PosY", _playerPosition.y}};
}

Player Player::fromJson(const json& _filename)
{
	return Player(_filename["Health"], _filename["PosX"], _filename["PosY"]);
}

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
	return json{{ "Health", _playerHealth }, {"PosX", _playerPosition.x}, {"PosY", _playerPosition.y}};
}

Player Player::fromJson(const json& _filename)
{
	return Player(_filename["Health"], _filename["PosX"], _filename["PosY"]);
}

void Player::PlayerController() {
	if (IsKeyDown(KEY_D) && _playerHealth > 0 && _playerPosition.x < GetMonitorWidth(GetCurrentMonitor()) + 1200 && !IsKeyDown(KEY_A) && _playerCanWalk) {
		_playerVelocity.x += _playerSpeed;
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			_playerVelocity.x *= 1.5;
		}
		_playerPosition.x += _playerVelocity.x;
	}
	if (IsKeyDown(KEY_A) && _playerHealth > 0 && _playerPosition.x > 0 && !IsKeyDown(KEY_D) && _playerCanWalk) {
		_playerVelocity.x -= _playerSpeed;
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			_playerVelocity.x *= 1.5;
		}
		_playerPosition.x += _playerVelocity.x;
	}
	if (IsKeyPressed(KEY_SPACE) && _playerHealth > 0 && !IsKeyPressedRepeat(KEY_SPACE) && _playerCanJump) {
		_playerJump = true;
	}

	_playerVelocity.y = 0;
	_playerVelocity.x = 0;
}

bool Player::IsPlayerJump() {
	return _playerJump;
}

float Player::GetJumpHeight() {
	return _jumpHeight;
}

bool Player::PlayerMaxJump() {
	if (_jumpHeight >= _jumpMaxHeight) {
		_playerJump = false;
		return true;
	}
	return false;
}

void Player::SetPlayerCanJump(bool playerCanJump) {
	_playerCanJump = playerCanJump;
}
bool Player::GetPlayerCanJump() {
	return _playerCanJump;
}

void Player::MoveVertically() {
	_jumpHeight += _playerJumpSpeed;
	_playerPosition.y -= _playerJumpSpeed;
	if (_playerJumpSpeed > 0.5f)
		_playerJumpSpeed -= 0.1f;
}
void Player::MoveVerticallyDown() {
	_jumpHeight = 0;
	_playerPosition.y += _playerJumpSpeed;
	if (_playerJumpSpeed <= 6.5f)
		_playerJumpSpeed += 0.3f;
}
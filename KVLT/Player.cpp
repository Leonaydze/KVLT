#include "Player.h"

short int Player::GetPlayerHealth(){
	return _playerHealth;
}

void Player::SetPlayerHealth(short int playerHealth){
	_playerHealth = playerHealth;
}

unsigned short int Player::GetMaxPlayerHealth()
{
	return _maxPlayerHealth;
}

void Player::HealPlayer(int healthAmount){
	_playerHealth += healthAmount;
	if (_playerHealth > _maxPlayerHealth) {
		_playerHealth = _maxPlayerHealth;
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
	return Player(_filename["id"], _filename["Health"], _filename["PosX"], _filename["PosY"]);
}

void Player::PlayerController() {
	if (IsKeyDown(KEY_D) && _playerHealth > 0 && _playerPosition.x < GetMonitorWidth(GetCurrentMonitor()) + 1200 && !IsKeyDown(KEY_A) && _playerCanWalk) {
		_playerVelocity.x += _playerSpeed;
		framesSpeed = 8;
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			_playerVelocity.x *= 1.25;
			framesSpeed = 10;
		}
		if (_frameRec.width < 0) {
			_frameRec.width = -_frameRec.width;
		}
		_playerPosition.x += _playerVelocity.x;

		framesCounter++;

		if (framesCounter >= (60 / framesSpeed))
		{
			framesCounter = 0;
			currentFrame++;

			if (currentFrame > 5) currentFrame = 0;

			if (_frameRec.x < 880) {
				if (currentFrame < 2) {
					_frameRec.x = (float)currentFrame * 111 + 10;
				}
				else if(currentFrame >= 2 && currentFrame != 3 && currentFrame != 4) {
					_frameRec.x = (float)currentFrame * 111 + 20;
				}
				else if (currentFrame == 3) {
					_frameRec.x = 412.0f;
				}
				else if (currentFrame == 4) {
					_frameRec.x = 576.0f;
				}
			}
			else {
				_frameRec.x = 0;
			}
		}
	}
	if (IsKeyDown(KEY_A) && _playerHealth > 0 && _playerPosition.x > 0 && !IsKeyDown(KEY_D) && _playerCanWalk) {
		_playerVelocity.x -= _playerSpeed;
		framesSpeed = 8;
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			framesSpeed = 10;
			_playerVelocity.x *= 1.25;
		}
		if (_frameRec.width > 0) {
			_frameRec.width = -_frameRec.width;
		}
		_playerPosition.x += _playerVelocity.x;

		framesCounter++;

		if (framesCounter >= (60 / framesSpeed))
		{
			framesCounter = 0;
			currentFrame++;

			if (currentFrame > 5) currentFrame = 0;

			if (_frameRec.x < 880) {
				if (currentFrame < 2) {
					_frameRec.x = (float)currentFrame * 111 + 10;
				}
				else if (currentFrame >= 2 && currentFrame != 3 && currentFrame != 4) {
					_frameRec.x = (float)currentFrame * 111 + 20;
				}
				else if (currentFrame == 3) {
					_frameRec.x = 412.0f;
				}
				else if (currentFrame == 4) {
					_frameRec.x = 576.0f;
				}
			}
			else {
				_frameRec.x = 0;
			}
		}
	}
	if (IsKeyPressed(KEY_SPACE) && _playerHealth > 0 && !IsKeyPressedRepeat(KEY_SPACE) && _playerCanJump) {
		_playerJump = true;
	}

	if (!IsKeyDown(KEY_LEFT_SHIFT) && (IsKeyDown(KEY_A) || IsKeyDown(KEY_D))) {
		_frameRec.y = 131;
	}
	else if (IsKeyDown(KEY_LEFT_SHIFT)) {
		_frameRec.y = 262;
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

void Player::Init(/*Player player*/)
{
	//this->SetPlayerPositionX(player.GetPlayerPositionX());
	//this->SetPlayerPositionY(player.GetPlayerPositionY());
	_playerTexture = LoadTexture("Sprites\\Player.png");
}

void Player::Draw()
{
	DrawTextureRec(_playerTexture, _frameRec, _playerPosition, WHITE);
	DrawRectangle((int)_playerPosition.x - 900, (int)_playerPosition.y - 650, _maxPlayerHealth * 2 + 10, 30, DARKBROWN);
	DrawRectangle((int)_playerPosition.x - 895, (int)_playerPosition.y - 645, GetPlayerHealth() * 2, 20, RED);
}
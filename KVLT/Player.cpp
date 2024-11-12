#include "Player.h"

bool Player::TriggerEvent(float interval) {
	float currentTime = (float)GetTime();

	if (currentTime - _lastUpdateTime >= interval) {
		_lastUpdateTime = currentTime;

		return true;
	}

	return false;
}

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

unsigned short int Player::GetHealthLevel()
{
	return _maxPlayerHealth / 10 % 10;
}

void Player::UpgradeHealthLevel(unsigned short int hpLvl){
	while (_maxPlayerHealth / 10 % 10 < hpLvl) {
		_maxPlayerHealth += 10;
	}
	if (_maxPlayerHealth / 10 % 10 > 5) {
		_maxPlayerHealth = 150;
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

unsigned short int Player::GetStaminaLevel()
{
	return _staminaLevel;
}

void Player::UpgradeStaminaLevel(unsigned short int staminaLvl){
	_staminaLevel = staminaLvl;
	while (_lastStaminaLevel < _staminaLevel) {
		_maxStamina++;
		_lastStaminaLevel++;
	}
	if (_staminaLevel > 4) {
		_maxStamina = 4;
	}
}

unsigned short int Player::GetCurrentStamina()
{
	return _stamina;
}

void Player::PlayerController() {
	if (IsKeyDown(KEY_D) && _playerCanWalk >= 0 && _playerHealth > 0 && _playerPosition.x < GetMonitorWidth(GetCurrentMonitor()) + 8000 && !IsKeyDown(KEY_A)) {
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
	if (IsKeyDown(KEY_A) && _playerCanWalk <= 0 && _playerHealth > 0 && _playerPosition.x > 0 && !IsKeyDown(KEY_D)) {
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
	if (IsKeyPressed(KEY_LEFT_ALT) && _playerHealth > 0 && _playerPosition.x > 0 && _stamina > 0) {
		if (IsKeyDown(KEY_A)) {
			_playerPosition.x -= _dashDistance + _dashLevel * 10;
			--_stamina;
			PlaySound(_dash);
		}
		if (IsKeyDown(KEY_D)) {
			_playerPosition.x += _dashDistance + _dashLevel * 10;
			--_stamina;
			PlaySound(_dash);
		}
	}
	if (TriggerEvent(2.5f) && _stamina < _maxStamina && !IsKeyDown(KEY_LEFT_SHIFT)) {
		++_stamina;
	}
	if (IsKeyPressed(KEY_SPACE) && _playerCanJump && _playerHealth > 0 && !IsKeyPressedRepeat(KEY_SPACE)) {
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

void Player::SetPlayerCanWalk(int playerCanWalk){
	_playerCanWalk = playerCanWalk;
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

unsigned short int Player::GetDashLevel()
{
	return _dashLevel;
}

void Player::UpgradeDashLevel(unsigned short int dashLvl){
	_dashLevel = dashLvl;
	while (_lastDashLevel < _dashLevel) {
		_lastDashLevel++;
	}
	if (_dashLevel > 5 ) {
		_dashLevel = 5;
	}
}

void Player::Init(/*Player player*/)
{
	//this->SetPlayerPositionX(player.GetPlayerPositionX());
	//this->SetPlayerPositionY(player.GetPlayerPositionY());
	_playerTexture = LoadTexture("Sprites\\Player.png");
	_dash = LoadSound("Sounds\\Dash.wav");
	_jump = LoadSound("Sounds\\Jump.mp3");
}

void Player::Draw()
{
	//player
	DrawTextureRec(_playerTexture, _frameRec, _playerPosition, WHITE);
	//Player health
	DrawRectangle((int)_playerPosition.x - 900, (int)_playerPosition.y - 650, _maxPlayerHealth * 2 + 10, 30, DARKBROWN);
	DrawRectangle((int)_playerPosition.x - 895, (int)_playerPosition.y - 645, _playerHealth * 2, 20, RED);
	//Player stamina
	DrawRectangle((int)_playerPosition.x - 900, (int)_playerPosition.y - 610, _maxStamina * 25 + 10, 30, DARKBROWN);
	DrawRectangle((int)_playerPosition.x - 895, (int)_playerPosition.y - 605, _stamina * 25, 20, DARKBLUE);
	DrawRectangle((int)_playerPosition.x - 872, (int)_playerPosition.y - 610, 4, 30, DARKBROWN);
	DrawRectangle((int)_playerPosition.x - 847, (int)_playerPosition.y - 610, 4, 30, DARKBROWN);
	DrawRectangle((int)_playerPosition.x - 822, (int)_playerPosition.y - 610, 4, 30, DARKBROWN);
	if (_maxStamina >= 5) {
		DrawRectangle((int)_playerPosition.x - 797, (int)_playerPosition.y - 610, 4, 30, DARKBROWN);
	}
	if (_maxStamina >= 6) {
		DrawRectangle((int)_playerPosition.x - 772, (int)_playerPosition.y - 610, 4, 30, DARKBROWN);
	}
	if (_maxStamina >= 7) {
		DrawRectangle((int)_playerPosition.x - 747, (int)_playerPosition.y - 610, 4, 30, DARKBROWN);
	}
	if (_maxStamina == 8) {
		DrawRectangle((int)_playerPosition.x - 722, (int)_playerPosition.y - 610, 4, 30, DARKBROWN);
	}
}

bool Player::PlayerDeath(){
	return _playerHealth <= 0;
}

void Player::PlayerTakesDamage(unsigned short int damage){
	_playerHealth -= damage;
}

void Player::Nullification()
{
	_staminaLevel = 0;
	_maxPlayerHealth = 100;
	_playerHealth = _maxPlayerHealth;
	_lastDashLevel = 0;
	_dashLevel = 0;
	_staminaLevel = 0;
	_maxStamina = 4;
	_stamina = _maxStamina;
	_playerPosition = { 0, 870 };
}

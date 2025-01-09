#include "Enemy.h"

Enemy::Enemy()
{
}

float Enemy::GetEnemyPosX(){
	return _enemyPosition.x;
}

void Enemy::SetEnemyPosX(float enemyPosX){
	_enemyPosition.x = enemyPosX;
}

float Enemy::GetEnemyPosY(){
	return _enemyPosition.y;
}

void Enemy::SetEnemyPosY(float enemyPosY){
	_enemyPosition.y = enemyPosY;
}

unsigned short int Enemy::GetEnemyDamage()
{
	return _enemyDamage;
}

void Enemy::SetEnemyDamage(int damage){
	_enemyDamage = damage;
}

bool Enemy::EnemyDeath(){
	return _enemyHealth <= 0;
}

short int Enemy::GetEnemyHealth(){
	return _enemyHealth;
}

void Enemy::EnemyGetDamage(unsigned short int damage){
	_enemyHealth -= damage;
}

void Enemy::Init()
{
	return;
}

void Enemy::Draw(){
	DrawTextureRec(_enemyTexture, _frameRec, _enemyPosition, WHITE);
	DrawRectangle(static_cast<int>(_enemyPosition.x), static_cast<int>(_enemyPosition.y - 20), _enemyHealth, 20, DARKBROWN);
	DrawRectangle(static_cast<int>(_enemyPosition.x + 5), static_cast<int>(_enemyPosition.y - 15), _enemyHealth - 10, 10, RED);
}

float Enemy::GetFrameRecX()
{
	return _frameRec.x;
}
float Enemy::GetFrameRecY()
{
	return _frameRec.y;
}

void Enemy::SetFrameRecX(float frameRecX)
{
	_frameRec.x = frameRecX;
}

void Enemy::SetFrameRecY(float frameRecY)
{
	_frameRec.y = frameRecY;
}

float Enemy::GetFrameRecWidth()
{
	return _frameRec.width;
}

float Enemy::GetFrameRecHeight()
{
	return _frameRec.height;
}

void Enemy::SetFrameRecWidth(float frameRecW)
{
	_frameRec.width = frameRecW;
}
void Enemy::SetFrameRecHeight(float frameRecH)
{
	_frameRec.height = frameRecH;
}

void Enemy::EnemyMoveX(float enemyMoveX){
	_enemyPosition.x += enemyMoveX;
}

float Enemy::GetEnemyAttackSpeed()
{
	return _enemyAttackSpeed;
}

float Enemy::GetEnemySpeed()
{
	return _enemySpeed;
}

bool Enemy::TakeDamageTime(float interval)
{
	float currentTime = static_cast<float>(GetTime());

	if (currentTime - _lUT >= interval) {
		_lUT = currentTime;

		return true;
	}

	return false;
}

Enemy::~Enemy()
{
	UnloadTexture(_enemyTexture);
}

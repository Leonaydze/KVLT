#include "Enemy.h"

Enemy::Enemy(int enemyHealth, int enemyDamage){
	_enemyHealth = enemyHealth;
	_enemyDamage = enemyDamage;
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

Enemy::_enemyClass Enemy::GetEnemyClass()
{
	return enemyClass;
}

void Enemy::EnemyDeath(){
	
}


#ifndef ENEMY_H
#define ENEMY_H
#include <raylib.h>

class Enemy{
protected:
	int _enemyHealth = 0;
	int _enemyDamage = 0;

	enum _enemyClass { Default, Vampire, Titan, Roc, Orc, Lich};

	_enemyClass enemyClass = Default;

	Vector2 _enemyPosition;
public:
	Enemy(int enemyHealth, int enemyDamage);

	float GetEnemyPosX();
	void SetEnemyPosX(float enemyPosX);

	float GetEnemyPosY();
	void SetEnemyPosY(float enemyPosY);

	_enemyClass GetEnemyClass();

	void EnemyDeath();
};

#endif // !ENEMY_H
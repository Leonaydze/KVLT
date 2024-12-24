#ifndef ENEMY_H
#define ENEMY_H
#include <raylib.h>

class Enemy{
protected:
	short int _enemyHealth = 0;
	unsigned short int _enemyDamage = 0;
	float _enemySpeed = 0;

	float _enemyAttackSpeed = 0;

	Vector2 _enemyPosition {};

	Texture2D _enemyTexture = LoadTexture("");
	Rectangle _frameRec = {0, 0, 0, 0};

public:
	Enemy();

	Enemy(Vector2 enemyPos, unsigned short int enemyHealth,  unsigned short int enemyDamage, float enemyAttackSpeed, float enemySpeed)
		: _enemyPosition(enemyPos), _enemyDamage(enemyDamage), _enemyHealth(enemyHealth), _enemyAttackSpeed(enemyAttackSpeed), _enemySpeed(enemySpeed) {}

	Enemy(int enemyHealth, int enemyDamage, Vector2 enemyPosition)
		: _enemyHealth(enemyHealth), _enemyDamage(enemyDamage), _enemyPosition(enemyPosition) {}

	float GetEnemyPosX();
	void SetEnemyPosX(float enemyPosX);

	float GetEnemyPosY();
	void SetEnemyPosY(float enemyPosY);

	unsigned short int GetEnemyDamage();
	void SetEnemyDamage(int damage);

	bool EnemyDeath();

	short int GetEnemyHealth();
	void EnemyGetDamage(unsigned short int damage);

	virtual void Init();
	void Draw();

	float GetFrameRecX();
	void SetFrameRecX(float frameRecX);

	float GetFrameRecY();
	void SetFrameRecY(float frameRecY);

	float GetFrameRecWidth();
	void SetFrameRecWidth(float frameRecW);

	float GetFrameRecHeight();
	void SetFrameRecHeight(float frameRecH);

	void EnemyMoveX(float enemyMoveX);

	float GetEnemyAttackSpeed();

	float GetEnemySpeed();
};

#endif // !ENEMY_H
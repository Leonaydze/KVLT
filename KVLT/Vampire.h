#ifndef VAMPIRE_H
#define VAMPIRE_H
#include "Enemy.h"


class Vampire : public Enemy{
public:
	Vampire(Vector2 enemyPos, short int enemyHealth, unsigned short int enemyDamage, float enemyAttackSpeed) 
		: Enemy(enemyPos, enemyHealth,enemyDamage, enemyAttackSpeed) {}

	void Init() override;
};

#endif // !VAMPIRE_H

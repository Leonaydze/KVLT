#ifndef VAMPIRE_H
#define VAMPIRE_H
#include "Enemy.h"


class Vampire : public Enemy{
public:
	Vampire() {}
	Vampire(Vector2 enemyPos) 
		: Enemy(enemyPos, 100, 10, 2.0f, 3.0f) {}

	void Init() override;

	float GetFrameRecWidth();

	void StealHP(int amount);
};

#endif // !VAMPIRE_H

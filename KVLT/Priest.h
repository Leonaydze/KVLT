#ifndef PRIEST_H
#define PRIEST_H
#include <raylib.h>

class Priest{
private:
	short int _npcHealth = 50;
	Vector2 _npcPosition = {};
public:
	Priest() {
		_npcHealth = 0;
		_npcPosition = {};
	}
	Priest(Vector2 npcPosition) : _npcPosition(npcPosition) {}

	short int GetNpcHealth();
	void ScaleNpcHealth(unsigned short int damage);

	float GetNpcPosX();
	float GetNpcPosY();

	bool NpcDeath();
};

#endif // !PRIEST_H



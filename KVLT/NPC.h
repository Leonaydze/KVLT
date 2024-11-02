#ifndef NPC_H
#define NPC_H

#include <raylib.h>

class NPC{
private:
	short int _npcHealth = 100;
	Vector2 _npcPosition = {};
	//enum _npcClass = {};
public:
	NPC() {}
	NPC(unsigned short int npcHealth, Vector2 npcPosition) 
		: _npcHealth(npcHealth), _npcPosition(npcPosition) {}

	short int GetNpcHealth();
	void ScaleNpcHealth(unsigned short int damage);

	float GetNpcPosX();
	float GetNpcPosY();

	bool NpcDeath();
};

#endif // !NPC_H

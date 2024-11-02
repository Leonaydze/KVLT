#include "NPC.h"

short int NPC::GetNpcHealth()
{
	return _npcHealth;
}

void NPC::ScaleNpcHealth(unsigned short int damage){
	_npcHealth -= damage;
}

float NPC::GetNpcPosX()
{
	return _npcPosition.x;
}

float NPC::GetNpcPosY()
{
	return _npcPosition.y;
}

bool NPC::NpcDeath()
{
	if (_npcHealth <= 0) {
		return true;
	}
	return false;
}



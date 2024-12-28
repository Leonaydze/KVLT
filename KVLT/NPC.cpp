#include "NPC.h"

NPC::NPC()
{
	_npcHealth = 0;
	_npcPosition = {};
	_currentAction = DEFAULT;
}

inline short int NPC::GetNpcHealth()
{
	return _npcHealth;
}

inline void NPC::ScaleNpcHealth(unsigned short int damage)
{
	_npcHealth -= damage;
}

inline float NPC::GetNpcPosX()
{
	return _npcPosition.x;
}

inline float NPC::GetNpcPosY()
{
	return _npcPosition.y;
}

inline bool NPC::NpcDeath()
{
	return _npcHealth < 1;
}

inline void NPC::Init() {}

void NPC::Draw()
{
	DrawTextureRec(_npcTexture, _frameRec, _npcPosition, WHITE);
}

NPC::_Action NPC::GetAction()
{
	return _currentAction;
}

NPC::~NPC()
{
	UnloadTexture(_npcTexture);
}

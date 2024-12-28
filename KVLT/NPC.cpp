#include "NPC.h"

NPC::NPC()
{
	_npcHealth = 0;
	_npcPosition = {};
	_currentAction = DEFAULT;
}

short int NPC::GetNpcHealth()
{
	return _npcHealth;
}

void NPC::ScaleNpcHealth(unsigned short int damage)
{
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
	return _npcHealth < 1;
}

void NPC::Init() {
	return;
}

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

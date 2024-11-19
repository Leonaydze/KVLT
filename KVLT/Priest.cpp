#include "Priest.h"

short int Priest::GetNpcHealth()
{
    return _npcHealth;
}

void Priest::ScaleNpcHealth(unsigned short int damage)
{
    _npcHealth -= damage;
}

float Priest::GetNpcPosX()
{
    return _npcPosition.x;
}

float Priest::GetNpcPosY()
{
    return _npcPosition.y;
}

bool Priest::NpcDeath()
{
    if (_npcHealth <= 0) {
        return true;
    }
    return false;
}

void Priest::Init(){
    _npcTexture = LoadTexture("Sprites\\Priest.png");
    _npcTexture.height = (int)(_npcTexture.height / 1.28f);
    _npcTexture.width = (int)(_npcTexture.width / 1.28f);
}

void Priest::Draw()
{
    DrawTextureRec(_npcTexture, _frameRec, _npcPosition, WHITE);
}

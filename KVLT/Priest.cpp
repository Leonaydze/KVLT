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
#include "Priest.h"

Priest::Priest()
{
}

void Priest::Init()
{
    this->_npcTexture = LoadTexture("Sprites\\Priest.png");
    this->_npcTexture.height = static_cast<int>(_npcTexture.height / 1.28f);
    this->_npcTexture.width = static_cast<int>(_npcTexture.width / 1.28f);
}

Priest::~Priest()
{
    UnloadTexture(_npcTexture);
}

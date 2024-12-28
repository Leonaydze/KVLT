#include "Priest.h"

Priest::Priest()
{
}

inline void Priest::Init()
{
    _npcTexture = LoadTexture("Sprites\\Priest.png");
    _npcTexture.height = static_cast<int>(_npcTexture.height / 1.28f);
    _npcTexture.width = static_cast<int>(_npcTexture.width / 1.28f);
}

Priest::~Priest()
{
    UnloadTexture(_npcTexture);
}

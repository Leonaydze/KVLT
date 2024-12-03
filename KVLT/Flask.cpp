#include "Flask.h"

int Flask::GetMaxHealCount()
{
    return _maxHealCount;
}

Texture2D Flask::GetTexture()
{
    return _flaskTexture;
}

void Flask::Init()
{
    _flaskTexture = LoadTexture("Sprites\\Flask.png");
    _flaskTexture.height = static_cast<int>(_flaskTexture.height * 1.5f);
    _flaskTexture.width = static_cast<int>(_flaskTexture.width * 1.5f);
}

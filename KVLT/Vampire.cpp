#include "Vampire.h"

void Vampire::Init(){
	_enemyTexture = LoadTexture("Sprites\\Vampire.png");

	SetFrameRecWidth(100);
	SetFrameRecHeight(128);
}

float Vampire::GetFrameRecWidth()
{
	return 100.0f;
}

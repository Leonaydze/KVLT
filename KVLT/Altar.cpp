#include "Altar.h"

void Altar::RegeneratePlayerHealth(Player &player){
	if (player.GetPlayerHealth() > 0 or player.GetPlayerHealth() < player.GetMaxPlayerHealth()) {
		player.HealPlayer(player.GetMaxPlayerHealth() - player.GetPlayerHealth());
		if (player.GetPlayerHealth() > player.GetMaxPlayerHealth()) {
			player.SetPlayerHealth(player.GetMaxPlayerHealth());
		}
	}
}

Altar::Altar(){
}

void Altar::Init()
{
	_altarTexture = LoadTexture("Sprites\\Altar.png");
	_altarTexture.height /= (int)2.5f;
	_altarTexture.width /= (int)2.5f;
}

void Altar::Draw()
{
	DrawTextureRec(_altarTexture, _altarRectangle, _altarPosition, WHITE);
}
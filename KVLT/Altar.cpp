#include "Altar.h"

void Altar::RegeneratePlayerHealth(Player &player){
	if (player.GetPlayerHealth() > 0 || player.GetPlayerHealth() < player.GetMaxPlayerHealth()) {
		player.HealPlayer(player.GetMaxPlayerHealth() - player.GetPlayerHealth());
		if (player.GetPlayerHealth() > player.GetMaxPlayerHealth()) {
			player.SetPlayerHealth(player.GetMaxPlayerHealth());
		}
	}
}

Altar::Altar(){
	_altarPosition = {-9999.0f, -9999.0f};
	_playerWasAtAltar = false;
}

void Altar::Init()
{
	_altarTexture = LoadTexture("Sprites\\Altar.png");
	_altarTexture.height = static_cast<int>(_altarTexture.height / 2.5f);
	_altarTexture.width = static_cast<int>(_altarTexture.width / 2.5f);
}

void Altar::Draw()
{
	DrawTextureRec(_altarTexture, _altarRectangle, _altarPosition, WHITE);
}

Vector2 Altar::GetAltarPosV()
{
	return _altarPosition;
}

bool Altar::GetPlayerWasAtAltar()
{
	return _playerWasAtAltar;
}

void Altar::SetPlayerWasAtAltar(bool flag)
{
	_playerWasAtAltar = flag;
}

float Altar::GetAltarPosX()
{
	return _altarPosition.x;
}

float Altar::GetAltarPosY()
{
	return _altarPosition.y;
}

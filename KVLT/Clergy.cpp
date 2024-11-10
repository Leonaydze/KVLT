#include "Clergy.h"

Clergy::Clergy(){
	_countClergy = 200;
}

int Clergy::GetClergyCount()
{
	return _countClergy;
}

json Clergy::toJson() const
{
	return json{ {"id", id}, {"CountClergy", _countClergy}};
}

Clergy Clergy::fromJson(const json& _filename)
{
	return Clergy(_filename["CountClergy"]);
}

void Clergy::Draw(Player& player, Font& font){
	DrawRectangle((int)player.GetPlayerPositionX() + 700, (int)player.GetPlayerPositionY() + 230, 130, 50, DARKBROWN);
	DrawRectangle((int)player.GetPlayerPositionX() + 705, (int)player.GetPlayerPositionY() + 235, 120, 40, BROWN);
	DrawTextEx(font, TextFormat(": %i", _countClergy), {player.GetPlayerPositionX() + 750, player.GetPlayerPositionY() + 245 }, 25, 3, RAYWHITE);
	DrawTexture(_clergyIcon, (int)player.GetPlayerPositionX() + 710, (int)player.GetPlayerPositionY() + 240, WHITE);
}

void Clergy::Init()
{
	_clergyIcon = LoadTexture("Sprites\\Clergy_icon.png");
}

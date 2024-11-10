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
	DrawRectangle((int)player.GetPlayerPositionX() + 670, (int)player.GetPlayerPositionY() + 260, 130, 50, DARKBROWN);
	DrawRectangle((int)player.GetPlayerPositionX() + 675, (int)player.GetPlayerPositionY() + 265, 120, 40, BROWN);
	DrawTextEx(font, TextFormat(": %i", _countClergy), {player.GetPlayerPositionX() + 720, player.GetPlayerPositionY() + 275 }, 25, 3, RAYWHITE);
	DrawTexture(_clergyIcon, (int)player.GetPlayerPositionX() + 680, (int)player.GetPlayerPositionY() + 270, WHITE);
}

void Clergy::Init()
{
	_clergyIcon = LoadTexture("Sprites\\Clergy_icon.png");
}

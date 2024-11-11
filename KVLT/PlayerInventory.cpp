#include "PlayerInventory.h"

void PlayerInventory::HealFlask(Player &player){
	if (_currentCountFlask >= 1 && IsKeyPressed(KEY_Q)) {
		player.HealPlayer(flask.GetMaxHealCount());
		_currentCountFlask--;
	}
}

PlayerInventory::PlayerInventory(){
	_currentCountFlask = 1;
}

int PlayerInventory::GetCurrentCountFlask()
{
	return _currentCountFlask;
}

json PlayerInventory::toJson() const
{
	return json{ {"id", id}, { "CurrentCountFlask", _currentCountFlask }};
}

PlayerInventory PlayerInventory::fromJson(const json& _filename)
{
	return PlayerInventory(_filename["CurrentCountFlask"]);
}

void PlayerInventory::Init()
{
	flask.Init();
}

void PlayerInventory::Draw(Player& player, Font font){
	DrawRectangle((int)player.GetPlayerPositionX() - 900, (int)player.GetPlayerPositionY() + 200, 98, 98, DARKBROWN);
	DrawRectangle((int)player.GetPlayerPositionX() - 898, (int)player.GetPlayerPositionY() + 202, 96, 96, BROWN);
	DrawTexture(flask.GetTexture(), (int)player.GetPlayerPositionX() - 898, (int)player.GetPlayerPositionY() + 202, WHITE);
	DrawTextEx(font, TextFormat("%i", _currentCountFlask), { player.GetPlayerPositionX() - 820, player.GetPlayerPositionY() + 270 }, 20, 2, RAYWHITE );
}

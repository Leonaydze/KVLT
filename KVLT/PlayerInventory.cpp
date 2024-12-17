#include "PlayerInventory.h"

void PlayerInventory::HealFlask(Player &player){
	if (_currentCountFlask >= 1 && IsKeyPressed(KEY_Q)) {
		player.HealPlayer(flask.GetMaxHealCount());
		_currentCountFlask--;
		PlaySound(_drinkFlask);
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

int PlayerInventory::GetFlaskHeal()
{
	return flask.GetMaxHealCount();
}

void PlayerInventory::Init(PlayerInventory pi)
{
	flask.Init();
	this->_currentCountFlask = pi._currentCountFlask;
	_drinkFlask = LoadSound("Sounds\\Drink_Flask.mp3");
}

void PlayerInventory::Draw(Player& player, Font font){
	DrawRectangle(static_cast<int>(player.GetPlayerPositionX()) - 900, static_cast<int>(player.GetPlayerPositionY()) + 200, 98, 98, DARKBROWN);
	DrawRectangle(static_cast<int>(player.GetPlayerPositionX()) - 895, static_cast<int>(player.GetPlayerPositionY()) + 205, 88, 88, BROWN);
	DrawTexture(flask.GetTexture(), static_cast<int>(player.GetPlayerPositionX()) - 898, static_cast<int>(player.GetPlayerPositionY()) + 202, WHITE);
	DrawTextEx(font, TextFormat("%i", _currentCountFlask), { player.GetPlayerPositionX() - 820, player.GetPlayerPositionY() + 270 }, 20, 2, RAYWHITE );
}

#include "PlayerInventory.h"

void PlayerInventory::HealFlask(Player &player, Flask flask){
	if (_currentCountFlask >= 1) {
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
	return json{ {"CurrentCountFlask", _currentCountFlask}};
}

PlayerInventory PlayerInventory::fromJson(const json& _filename)
{
	return PlayerInventory(_filename["CurrentCountFlask"]);
}

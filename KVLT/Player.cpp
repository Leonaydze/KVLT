#include "Player.h"

int Player::GetPlayerHealth()
{
	return _playerHealth;
}

void Player::HealPlayer(int healthAmount){
	_playerHealth += healthAmount;
}

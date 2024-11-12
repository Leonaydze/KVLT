#include "PlayerWeapon.h"


PlayerWeapon::PlayerWeapon(_WeaponWeight currentWW) {
	SetDamageAndSpeedDueToWeight(currentWW);
}

void PlayerWeapon::SetDamageAndSpeedDueToWeight(_WeaponWeight currentWW)
{
	if (currentWW == LIGHT) {
		_weaponDamage = 10;
		_weaponSpeed = 1.0f;
		return;
	}
	if (currentWW == MEDIUM) {
		_weaponDamage = 20;
		_weaponSpeed = 2.0f;
		return;
	}
	if (currentWW == HEAVY) {
		_weaponDamage = 40;
		_weaponSpeed = 4.0f;
		return;
	}
	return;
}

PlayerWeapon::PlayerWeapon(){

}

json PlayerWeapon::toJson() const
{
	return json{ {"id", id}, { "CurrentWeaponWeight", currentWW }, {"WeaponDamage", _weaponDamage}, {"WeaponSpeed", _weaponSpeed}};
}

PlayerWeapon PlayerWeapon::fromJson(const json& _filename)
{
	return PlayerWeapon(_filename["CurrentWeaponWeight"], _filename["WeaponDamage"], _filename["WeaponSpeed"]);
}

unsigned short int PlayerWeapon::GetWeaponDamage()
{
	return _weaponDamage;
}

float PlayerWeapon::GetWeaponSpeed()
{
	return _weaponSpeed;
}

PlayerWeapon::_WeaponWeight PlayerWeapon::GetCurrentWeight()
{
	return currentWW;
}

void PlayerWeapon::SetRandomDamage(){
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		int result = rand() % 2;
		switch (result){
			case 0:
				_weaponDamage -= rand() % 5;
				break;
			case 1:
				_weaponDamage += rand() % 5;
				break;
		}
	}
	else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		SetDamageAndSpeedDueToWeight(currentWW);
	}
}


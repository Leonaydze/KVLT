#include "PlayerWeapon.h"

int PlayerWeapon::GetWeaponWeight()
{
	return currentWW;
}

PlayerWeapon::PlayerWeapon(){
	if (GetWeaponWeight() == LIGHT) {
		_weaponDamage = 10;
		_weaponSpeed = 1.0;
	}
	if (GetWeaponWeight() == MEDIUM) {
		_weaponDamage = 20;
		_weaponSpeed = 2.0;
	}
	if (GetWeaponWeight() == HEAVY) {
		_weaponDamage = 40;
		_weaponSpeed = 4.0;
	}
}

json PlayerWeapon::toJson() const
{
	return json{ {"id", id} ,{"CurrentWeaponWeight", currentWW}, {"WeaponDamage", _weaponDamage}, {"WeaponSpeed", _weaponSpeed}};
}

PlayerWeapon PlayerWeapon::fromJson(const json& _filename)
{
	return PlayerWeapon(_filename["CurrentWeaponWeight"], _filename["WeaponDamage"], _filename["WeaponSpeed"]);
}

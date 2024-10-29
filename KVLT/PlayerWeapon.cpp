#include "PlayerWeapon.h"

int PlayerWeapon::GetWeaponWeight()
{
	return currentWW;
}

void PlayerWeapon::SetDamageAndSpeedDueToWeight()
{
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

void PlayerWeapon::SetRandomDamege(){
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
		SetDamageAndSpeedDueToWeight();
	}
}


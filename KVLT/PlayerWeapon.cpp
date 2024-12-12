#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon() {
	SetDamageAndSpeedDueToWeight(currentWW);
}

PlayerWeapon::PlayerWeapon(_WeaponWeight currentWW) {
	SetDamageAndSpeedDueToWeight(currentWW);
}

void PlayerWeapon::SetDamageAndSpeedDueToWeight(_WeaponWeight currentWW)
{
	if (currentWW == LIGHT) {
		_weaponDamage = 10;
		_weaponSpeed = 1.0f;
		_attack = LoadSound("Sounds\\Weapon_light.wav");
		return;
	}
	if (currentWW == MEDIUM) {
		_weaponDamage = 20;
		_weaponSpeed = 1.5f;
		_attack = LoadSound("Sounds\\Weapon_medium.wav");
		return;
	}
	if (currentWW == HEAVY) {
		_weaponDamage = 40;
		_weaponSpeed = 2.5f;
		_attack = LoadSound("Sounds\\Weapon_heavy.wav");
		return;
	}
	return;
}

void PlayerWeapon::AttackSound()
{
	PlaySound(_attack);
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


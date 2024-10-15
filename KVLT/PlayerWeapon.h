#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class PlayerWeapon{
private:
	enum _WeaponWeight {LIGHT, MEDIUM, HEAVY};
	_WeaponWeight currentWW = LIGHT;
	unsigned short int _weaponDamage = 0;
	float _weaponSpeed = 0;
	int GetWeaponWeight();
public:
	int id = -1;

	PlayerWeapon();

	PlayerWeapon(_WeaponWeight currentWW, unsigned short int weaponDamage, float weaponSpeed)
		: currentWW(currentWW), _weaponDamage(weaponDamage), _weaponSpeed(weaponSpeed) {}

	PlayerWeapon(int id, const PlayerWeapon& other)
		: currentWW(other.currentWW), _weaponDamage(other._weaponDamage), _weaponSpeed(other._weaponSpeed) {}

	json toJson() const;
	static PlayerWeapon fromJson(const json& _filename);
};


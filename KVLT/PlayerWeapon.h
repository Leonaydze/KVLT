#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <raylib.h>

using json = nlohmann::json;

class PlayerWeapon{
private:
	unsigned short int _weaponDamage = 0;
	float _weaponSpeed = 0;
	Sound _attack = LoadSound("");
public:
	enum _WeaponWeight { LIGHT, MEDIUM, HEAVY };
	_WeaponWeight currentWW = LIGHT;

	int id = -1;

	PlayerWeapon();

	PlayerWeapon(_WeaponWeight currentWW);

	PlayerWeapon(_WeaponWeight currentWW, unsigned short int weaponDamage, float weaponSpeed)
		: currentWW(currentWW), _weaponDamage(weaponDamage), _weaponSpeed(weaponSpeed) {}

	PlayerWeapon(int id, const PlayerWeapon& other)
		: currentWW(other.currentWW), _weaponDamage(other._weaponDamage), _weaponSpeed(other._weaponSpeed) {}

	json toJson() const;
	static PlayerWeapon fromJson(const json& _filename);

	unsigned short int GetWeaponDamage();

	void SetRandomDamage();

	float GetWeaponSpeed();

	PlayerWeapon::_WeaponWeight GetCurrentWeight();

	void SetDamageAndSpeedDueToWeight(_WeaponWeight currentWW);

	void AttackSound();

	void Init(PlayerWeapon pw);

	~PlayerWeapon();
};


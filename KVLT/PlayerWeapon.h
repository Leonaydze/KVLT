#pragma once
class PlayerWeapon{
private:
	enum _WeaponWeight {LIGHT, MEDIUM, HEAVY};
	_WeaponWeight currentWW = LIGHT;
	int _weaponDamage = 0;
	float _weaponSpeed = 0;
	int GetWeaponWeight();
public:
	PlayerWeapon(int weaponDamage, float weaponSpeed);
};


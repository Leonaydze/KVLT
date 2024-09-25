#include "PlayerWeapon.h"

int PlayerWeapon::GetWeaponWeight()
{
	return currentWW;
}

PlayerWeapon::PlayerWeapon(int weaponDamage, float weaponSpeed){
	if (GetWeaponWeight() == LIGHT) {
		weaponDamage = 10;
		weaponSpeed = 1.0;
	}
	if (GetWeaponWeight() == MEDIUM) {
		weaponDamage = 20;
		weaponSpeed = 2.0;
	}
	if (GetWeaponWeight() == HEAVY) {
		weaponDamage = 40;
		weaponSpeed = 4.0;
	}
}

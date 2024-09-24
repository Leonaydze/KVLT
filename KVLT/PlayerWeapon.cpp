#include "PlayerWeapon.h"

int PlayerWeapon::GetWeaponWeight()
{
	return currentWW;
}

PlayerWeapon::PlayerWeapon(int weaponDamage, float weaponSpeed){
	if (currentWW == LIGHT) {
		weaponDamage = 10;
		weaponSpeed = 4.0;
	}
	if (currentWW == MEDIUM) {
		weaponDamage = 20;
		weaponSpeed = 3.0;
	}
	if (currentWW == HEAVY) {
		weaponDamage = 40;
		weaponSpeed = 1.0;
	}
}

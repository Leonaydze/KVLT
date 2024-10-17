#include "PlayerService.h"

PlayerService::PlayerService() : dataSource("Save\\PlayerData.json") {}

void PlayerService::create(const Player& player) {
	Service::create(dataSource, player);
}
vector<Player> PlayerService::read() {
	return Service::read(dataSource);
}
void PlayerService::update(const Player& player) {
	Service::update(dataSource, player);
}
void PlayerService::remove(int id) {
	Service::remove(dataSource, id);
}

PlayerInventoryService::PlayerInventoryService() : dataSource("Save\\PlayerInventoryData.json") {}

void PlayerInventoryService::create(const PlayerInventory& playerInventory){
	Service::create(dataSource, playerInventory);
}
vector<PlayerInventory> PlayerInventoryService::read() {
	return Service::read(dataSource);
}
void PlayerInventoryService::update(const PlayerInventory& playerInventory) {
	Service::update(dataSource, playerInventory);
}
void PlayerInventoryService::remove(int id) {
	Service::remove(dataSource, id);
}

PlayerWeaponService::PlayerWeaponService() : dataSource("Save\\PlayerWeaponData.json"){
}

void PlayerWeaponService::create(const PlayerWeapon& playerWeapon) {
	Service::create(dataSource, playerWeapon);
}
vector<PlayerWeapon> PlayerWeaponService::read() {
	return Service::read(dataSource);
}
void PlayerWeaponService::update(const PlayerWeapon& playerWeapon) {
	Service::update(dataSource, playerWeapon);
}
void PlayerWeaponService::remove(int id) {
	Service::remove(dataSource, id);
}

PlayerClergyService::PlayerClergyService() : dataSource("Save\\PlayerClergyData.json") {
}

void PlayerClergyService::create(const Clergy& playerClergy) {
	Service::create(dataSource, playerClergy);
}
vector<Clergy> PlayerClergyService::read() {
	return Service::read(dataSource);
}
void PlayerClergyService::update(const Clergy& playerClergy) {
	Service::update(dataSource, playerClergy);
}
void PlayerClergyService::remove(int id) {
	Service::remove(dataSource, id);
}
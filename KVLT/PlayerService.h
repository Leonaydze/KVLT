#ifndef PLAYERSERVICE_H
#define PLAYERSERVICE_H

#include "DataSource.h"
#include "Service.h"

class PlayerService : public Service<Player> {
private:
	DataSource<Player> dataSource;
public:
	PlayerService();

	void create(const Player& player);
	Player read();
	void update(const Player& player);
	void remove(int id);
};

class PlayerInventoryService : public Service<PlayerInventory> {
private:
	DataSource<PlayerInventory> dataSource;
public:
	PlayerInventoryService();

	void create(const PlayerInventory& playerInventory);
	PlayerInventory read();
	void update(const PlayerInventory& playerInventory);
	void remove(int id);
};

class PlayerWeaponService : public Service<PlayerWeapon> {
private:
	DataSource<PlayerWeapon> dataSource;
public:
	PlayerWeaponService();

	void create(const PlayerWeapon& playerWeapon);
	PlayerWeapon read();
	void update(const PlayerWeapon& playerWeapon);
	void remove(int id);
};

class PlayerClergyService : public Service<Clergy> {
private:
	DataSource<Clergy> dataSource;
public:
	PlayerClergyService();

	void create(const Clergy& playerClergy);
	Clergy read();
	void update(const Clergy& playerClergy);
	void remove(int id);
};

#endif // !PLAYERSERVICE_H

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
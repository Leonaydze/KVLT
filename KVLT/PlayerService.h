#ifndef PLAYERSERVICE_H
#define PLAYERSERVICE_H

#include "DataSource.h"
#include "Service.h"
//#include "Player.h"

class PlayerService : public Service<Player> {
private:
	DataSource<Player> dataSource;
public:
	PlayerService();

	void create(const Player& player);
	vector<Player> read();
	void update(const Player& player);
	void remove(int id);
};

#endif // !PLAYERSERVICE_H

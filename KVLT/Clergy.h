#ifndef CLERGY_H
#define CLERGY_H

#include "Player.h"
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class Clergy {
private:
	int _countClergy;

	Texture2D _clergyIcon = LoadTexture("");
public:
	int id = -1;
	
	Clergy();

	Clergy(int countClergy) : _countClergy(countClergy) {}
	
	Clergy(int id, const Clergy& other) : _countClergy(other._countClergy) {}

	int GetClergyCount();

	json toJson() const;
	static Clergy fromJson(const json& _filename);

	void Draw(Player& player, Font& font);

	void Init();
};

#endif // !CLERGY_H


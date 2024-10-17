#ifndef CLERGY_H
#define CLERGY_H

#include <raylib.h>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class Clergy {
private:
	int _countClergy;

public:
	int id = -1;
	
	Clergy();

	Clergy(int countClergy) : _countClergy(countClergy) {}
	
	Clergy(int id, const Clergy& other) : _countClergy(other._countClergy) {}

	int GetClergyCount();

	json toJson() const;
	static Clergy fromJson(const json& _filename);
};

#endif // !CLERGY_H


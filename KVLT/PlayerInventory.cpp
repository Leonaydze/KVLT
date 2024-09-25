#include "PlayerInventory.h"

void PlayerInventory::HealFlask(Player &player, Flask flask){
	if (_currentCountFlax >= 1) {
		player.HealPlayer(flask.GetMaxHealCount());
		_currentCountFlax--;
	}
}

PlayerInventory::PlayerInventory(){
	_currentCountFlax = 1;
}

int PlayerInventory::GetCurrentCountFlask()
{
	return _currentCountFlax;
}

void PlayerInventory::Create() {
	json j;
	//Read
	std::ifstream inputFile(_filename);
	if (inputFile) {
		inputFile >> j;
	}

	//New Entity
	json newEntry = { { "Flask" , _currentCountFlax } };
	j.push_back(newEntry);

	//Save File
	std::ofstream outputFile(_filename);
	outputFile << j.dump(4);
	outputFile.close();
}

void PlayerInventory::Read() {
	json j;
	//Read
	std::ifstream inputFile(_filename);
	if (inputFile) {
		inputFile >> j;
		//Output On Screen
		std::cout << j.dump(4) << "\n";
	}
	else {
		std::cout << "FileNotFound" << std::endl;
	}
}

void PlayerInventory::Update(unsigned short int index) {
	json j;
	//Read
	std::ifstream inputFile(_filename);
	if (inputFile) {
		inputFile >> j;
		//Проверка в диапозоне ли индекс
		if (index < 0 or index >= j.size()) {
			std::cout << "Index is out of range" << std::endl;
			return;
		}
		j[index]["Count Flask"] = _currentCountFlax;

		//Save File
		std::ofstream outputFile(_filename);
		outputFile << j.dump(4);
		outputFile.close();
	}
	else {
		std::cout << "FileNotFound" << std::endl;
	}
}

void PlayerInventory::Remove(unsigned short int index) {
	json j;
	//Read
	std::ifstream inputFile(_filename);
	if (inputFile) {
		inputFile >> j;
		//Проверка в диапозоне ли индекс
		if (index < 0 or index >= j.size()) {
			std::cout << "Index is out of range" << std::endl;
			return;
		}
		j.erase(j.begin() + index);
		//Save File
		std::ofstream outputFile(_filename);
		outputFile << j.dump(4);
		outputFile.close();
	}
	else {
		std::cout << "FileNotFound" << std::endl;
	}
}
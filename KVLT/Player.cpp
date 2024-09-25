#include "Player.h"

void Player::Create(){
	json j;
	//Read
	std::ifstream inputFile(_filename);
	if (inputFile) {
		inputFile >> j;
	}

	//New Entity
	json newEntry = { { "Health" , _playerHealth }, { "Position X" , _playerPosition.x }, { "Position Y" , _playerPosition.y } };
	j.push_back(newEntry);

	//Save File
	std::ofstream outputFile(_filename);
	outputFile << j.dump(4);
	outputFile.close();
}

void Player::Read(){
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

void Player::Update(unsigned short int index){
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
		j[index]["Health"] = _playerHealth;
		j[index]["Position X"] = _playerPosition.x;
		j[index]["Position Y"] = _playerPosition.y;
		//Save File
		std::ofstream outputFile(_filename);
		outputFile << j.dump(4);
		outputFile.close();
	}
	else {
		std::cout << "FileNotFound" << std::endl;
	}
}

void Player::Remove(unsigned short int index){
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

Player::Player()
{
}

int Player::GetPlayerHealth(){
	return _playerHealth;
}

void Player::HealPlayer(int healthAmount){
	_playerHealth += healthAmount;
}

Vector2 Player::GetPlayerPositionV(){
	return _playerPosition;
}

void Player::SetPlayerPositionV(Vector2 playerPosition){
	_playerPosition = playerPosition;
}

float Player::GetPlayerPositionX(){
	return _playerPosition.x;
}

void Player::SetPlayerPositionX(float playerPosX){
	_playerPosition.x = playerPosX;
}

float Player::GetPlayerPositionY(){
	return _playerPosition.y;
}

void Player::SetPlayerPositionY(float playerPosY){
	_playerPosition.y = playerPosY;
}


#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Player.h"
#include "PlayerInventory.h"

using json = nlohmann::json;

class Animal {
public:
	int id;
	std::string name;
	std::string breed;
	double weight;

	Animal(int id, const std::string &name, const std::string &breed, double weight)
		: id(id), name(name), breed(breed), weight(weight) {}

	json toJson() const {
		return json{ {"id", id} , 
			{"name", name} , 
			{"breed", breed},
			{"weight", weight} };
	}
	Animal fromJson(const json& _fileName) {
		return Animal(_fileName["id"],_fileName["name"],_fileName["breed"],_fileName["weight"]);
	}
};

template <typename T>
class DataSource {
private:
	static const std::string _fileName;

	static json readFile() {
		json j;
		//Read
		std::ifstream inputFile(_fileName);
		if (inputFile) {
			inputFile >> j;
		}
		return j;
	}

	static void writeFile(const json &j) {
		std::ofstream outputFile(_fileName);
		outputFile << j.dump(4);
	}

	/// <summary>
	/// Функция поиска по идентификатору
	/// </summary>
	/// <param name="id">Идентификатор</param>
	/// <returns>Индекс элемента или -1, если он не был найден</returns>
	int FindById(int id) {
		int index = -1;
		json j = readFile();

		for (int i = 0; i < j.size(); i++) {
			if (j[i]["id"] == id) {
				index = i;
				break;
			}
		}

		return index;
	}
public:
	void Create(const T &item) {
		json j = readFile();

		j.push_back(item.toJson());
		writeFile(j);
	}

	void Read() {
		json j = readFile();
		std::cout << j.dump(4) << std::endl;
	}

	void Update(const T &item) {
		json j = readFile();
		int index = FindById(item.id);
		if (index != -1) {
			j[index] = item.toJson();
			writeFile(j);
		}
		else {
			std::cout << "Index is out of range" << std::endl;
			return;
		}
	}

	void Remove(int id) {
		json j = readFile();
		int index = FindById(id);
		if (index != - 1) {
			j.erase(j.begin() + index);
			writeFile(j);
		}
		else {
			std::cout << "Index is out of range" << std::endl;
			return;

		}
	}
};

template <typename T>
const std::string DataSource<T>::_fileName = "data.json";

int main(){
	DataSource<Animal> dataSource;

	Animal a1(1, "Bobik", "Dog", 10);
	dataSource.Create(a1);
	dataSource.Read();

	Animal updA1(1, "Bobik", "Dog", 20);
	dataSource.Update(updA1);

	dataSource.Read();
	dataSource.Remove(1);
}

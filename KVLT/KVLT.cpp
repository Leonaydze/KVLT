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
	json data;
	int currentId;

	void readFile() {
		std::ifstream inputFile(_fileName);
		if (inputFile) {
			inputFile >> data;
			currentId = data.empty() ? 1 : data.back()["id"] + 1;
		}
		else {
			currentId = 1;
		}
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

		for (int i = 0; i < data.size(); i++) {
			if (data[i]["id"] == id) {
				index = i;
				break;
			}
		}

		return index;
	}
public:
	DataSource() {
		readFile();
	}
	~DataSource() {
		writeFile(data);
	}

	void Create(const T &item) {
		T next(currentId, item.name, item.breed, item.weight);
		data.push_back(item.toJson());
		currentId++;
		writeFile(data);
	}

	void Read() {
		std::cout << data.dump(4) << std::endl;
	}

	void Update(const T &item) {
		int index = FindById(item.id);
		if (index != -1) {
			data[index] = item.toJson();
			writeFile(data);
		}
		else {
			std::cout << "Index is out of range" << std::endl;
			return;
		}
	}

	void Remove(int id) {
		int index = FindById(id);
		if (index != - 1) {
			data.erase(data.begin() + index);
			writeFile(data);
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

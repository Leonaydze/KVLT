#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>

using json = nlohmann::json;

class Animal {
public:
	int id;
	std::string name;
	std::string breed;
	double weight;

	Animal(int id, const std::string &name, const std::string &breed, double weight)
		: id(id), name(name), breed(breed), weight(weight) {}

	// Конструктор копирования
	Animal(int id, const Animal& other) : id(id), name(other.name), breed(other.breed), weight(other.weight) {}

	json toJson() const {
		return json{ {"id", id} , 
			{"name", name} , 
			{"breed", breed},
			{"weight", weight} };
	}
	static Animal fromJson(const json& _fileName) {
		return Animal(_fileName["id"],_fileName["name"],_fileName["breed"],_fileName["weight"]);
	}
};

class Task {
private:
	int id;
	std::string title;
	std::string description;

public:
	Task(int id, const std::string& title, const std::string& description)
		: id(id), title(title), description(description) {}


	json toJson() const {
		return json{ {"id", id} ,
			{"title", title} ,
			{"description", description} };
	}

	static Task fromJson(const json& _fileName) {
		return Task(_fileName["id"], _fileName["title"], _fileName["description"]);
	}
};


class Service {
public:
	template <typename T>
	void create(DataSource<T> &dataSource, const T &item) {
		dataSource.Create(item);
	}

	template <typename T>
	std::vector<T> read(DataSource<T> &dataSource) {
		return dataSource.Read();
	}

	template <typename T>
	void update(DataSource<T> &dataSource, const T &item) {
		dataSource.Update(item);
	}

	template <typename T>
	void remove(DataSource<T> &dataSource, int id) {
		dataSource.Remove(id);
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
	DataSource(std::string filename) {
		this->_fileName = filename;
		readFile();
	}
	~DataSource() {
		writeFile(data);
	}

	void Create(const T &item) {
		T next(currentId, item);
		data.push_back(item.toJson());
		currentId++;
		writeFile(data);
	}

	std::vector<T> Read() {
		std::vector<T> items;
		for (const auto& j : data) {
			items.push_back(T::fromJson(j));
		}
		return items;
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

}

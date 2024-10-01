#pragma once
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

	static void writeFile(const json& j) {
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

	void Create(const T& item) {
		T next(currentId, item.name, item.breed, item.weight);
		data.push_back(item.toJson());
		currentId++;
		writeFile(data);
	}

	void Read() {
		std::cout << data.dump(4) << std::endl;
	}

	void Update(const T& item) {
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
		if (index != -1) {
			data.erase(data.begin() + index);
			writeFile(data);
		}
		else {
			std::cout << "Index is out of range" << std::endl;
			return;
		}
	}
};
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <raylib.h>

using json = nlohmann::json;
using namespace std;

class Animal {
public:
	int id;
	string name;
	string breed;
	double weight;

	Animal(int id, const string& name, const string& breed, double weight)
		: id(id), name(name), breed(breed), weight(weight) {}

	// Конструктор копирования
	Animal(int id, const Animal& other)
		: id(id), name(other.name), breed(other.breed), weight(other.weight) {}

	json toJson() const {
		return json{
			{"id",id},
			{"name",name},
			{"breed", breed},
			{"weight",weight}
		};
	}

	static Animal fromJson(const json& j) {
		return Animal(j["id"], j["name"], j["breed"], j["weight"]);
	}

	string ToString() {
		return to_string(id)
			+ " " + name
			+ " " + breed
			+ " " + to_string(weight);
	}

};


class Task {
public:
	int id;
	string title;
	string description;

	Task(int id, const string& title, const string& description)
		: id(id), title(title), description(description) {}

	// Конструктор копирования
	Task(int id, const Task& other)
		: id(id), title(other.title), description(other.description) {}

	json toJson() const {
		return json{
			{"id",id},
			{"title",title},
			{"description", description}
		};
	}

	static Task fromJson(const json& j) {
		return Task(j["id"], j["title"], j["description"]);
	}

	string ToString() {
		return to_string(id)
			+ " " + title
			+ " " + description;
	}

};

template <typename T>
class DataSource {
private:
	string filename;
	json data;
	int currentId;

	void readFile() {
		ifstream inputFile(filename);
		if (inputFile) {
			inputFile >> data;
			currentId = data.empty() ? 1 : data.back()["id"] + 1;
		}
		else {
			currentId = 1;
		}
	}

	void writeFile(const json& j) {
		ofstream outputFile(filename);
		outputFile << j.dump(4);
	}

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

	DataSource(string filename) {
		this->filename = filename;
		readFile();
	}

	~DataSource() {
		writeFile(data);
	}

	void create(const T& item) {
		T next(currentId, item);
		data.push_back(next.toJson());
		currentId++;
		writeFile(data);
	}

	vector<T> read() {
		vector<T> items;
		for (const auto& j : data) {
			items.push_back(T::fromJson(j));
		}
		return items;
	}

	void update(const T& item) {
		int index = FindById(item.id);
		if (index != -1)
		{
			data[index] = item.toJson();
			writeFile(data);
		}
		else {
			cout << "Index is out of range!" << endl;
		}
	}

	void remove(int id) {
		int index = FindById(id);
		if (index != -1) {
			data.erase(data.begin() + index);
			writeFile(data);
		}
		else {
			cout << "Index is out of range!" << endl;
		}
	}
};

class Service {
public:
	template <typename T>
	void create(DataSource<T>& dataSource, const T& item) {
		dataSource.create(item);
	}
	template <typename T>
	vector<T> read(DataSource<T>& dataSource) {
		return dataSource.read();
	}
	template <typename T>
	void update(DataSource<T>& dataSource, const T& item) {
		dataSource.update(item);
	}
	template <typename T>
	void remove(DataSource<T>& dataSource, int id) {
		dataSource.remove(id);
	}
};

class AnimalService : public Service {
private:
	DataSource<Animal> dataSource;
public:
	AnimalService() :dataSource("animals.json") {}
	void create(const Animal& animal) {
		Service::create(dataSource, animal);
	}
	vector<Animal> read() {
		return Service::read(dataSource);
	}
	void update(const Animal& animal) {
		Service::update(dataSource, animal);
	}
	void remove(int id) {
		Service::remove(dataSource, id);
	}
};

class TaskService : public Service {
private:
	DataSource<Task> dataSource;
public:
	TaskService() :dataSource("tasks.json") {}
	void create(const Task& task) {
		Service::create(dataSource, task);
	}
	vector<Task> read() {
		return Service::read(dataSource);
	}
	void update(const Task& task) {
		Service::update(dataSource, task);
	}
	void remove(int id) {
		Service::remove(dataSource, id);
	}
};

template <typename T>
void PrintList(vector<T> list) {
	for (auto& item : list) {
		cout << item.ToString() << endl;
	}
}

bool _exitWindowRequested = false;
bool _exitWindow = false;

bool GetExitWindow() {
	return _exitWindow;
}
void SetExitWindow(bool exitWindow) {
	_exitWindow = exitWindow;
}

bool GetExitWindowRequest() {
	return _exitWindowRequested;
}
void SetExitWindowRequest(bool exitWindowRequest) {
	_exitWindowRequested = exitWindowRequest;
}


int main()
{
	setlocale(0, "ru");

	InitWindow(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), "KVLT");
	//GuiLoadStyle("myStyle.rgs");

	SetExitKey(KEY_NULL);

	bool showMessageBox = false;
	
	SetTargetFPS(60);

	Font font = LoadFont("Font.png");
	GuiSetFont(font);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
	GuiSetStyle(DEFAULT, TEXT_SPACING, 2);

	while (!GetExitWindow())
	{
		if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) {
			SetExitWindowRequest(true);
			showMessageBox = true;
		}

		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
		
		if (GetExitWindowRequest() || showMessageBox) {
			int result = GuiMessageBox({(float)GetMonitorWidth(GetCurrentMonitor()) / 2 - 125, (float)GetMonitorHeight(GetCurrentMonitor()) / 2 - 50, 250, 100 },
				"#193#Quit?", "Are You Want To Quit?", "Yes;No");
			if(result == 1) SetExitWindow(true);
			else if (result == 2) {
				SetExitWindowRequest(false);
				showMessageBox = false;
			}
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

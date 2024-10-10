#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <raylib.h>
#include <ctime>

using json = nlohmann::json;
using namespace std;

//class Animal {
//public:
//	int id;
//	string name;
//	string breed;
//	double weight;
//
//	Animal(int id, const string& name, const string& breed, double weight)
//		: id(id), name(name), breed(breed), weight(weight) {}
//
//	// Конструктор копирования
//	Animal(int id, const Animal& other)
//		: id(id), name(other.name), breed(other.breed), weight(other.weight) {}
//
//	json toJson() const {
//		return json{
//			{"id",id},
//			{"name",name},
//			{"breed", breed},
//			{"weight",weight}
//		};
//	}
//
//	static Animal fromJson(const json& j) {
//		return Animal(j["id"], j["name"], j["breed"], j["weight"]);
//	}
//
//	string ToString() {
//		return to_string(id)
//			+ " " + name
//			+ " " + breed
//			+ " " + to_string(weight);
//	}
//
//};
//
//
//
//class AnimalService : public Service {
//private:
//	DataSource<Animal> dataSource;
//public:
//	AnimalService() :dataSource("animals.json") {}
//	void create(const Animal& animal) {
//		Service::create(dataSource, animal);
//	}
//	vector<Animal> read() {
//		return Service::read(dataSource);
//	}
//	void update(const Animal& animal) {
//		Service::update(dataSource, animal);
//	}
//	void remove(int id) {
//		Service::remove(dataSource, id);
//	}
//};
//
//class TaskService : public Service {
//private:
//	DataSource<Task> dataSource;
//public:
//	TaskService() :dataSource("tasks.json") {}
//	void create(const Task& task) {
//		Service::create(dataSource, task);
//	}
//	vector<Task> read() {
//		return Service::read(dataSource);
//	}
//	void update(const Task& task) {
//		Service::update(dataSource, task);
//	}
//	void remove(int id) {
//		Service::remove(dataSource, id);
//	}
//};
//
//template <typename T>
//void PrintList(vector<T> list) {
//	for (auto& item : list) {
//		cout << item.ToString() << endl;
//	}
//}

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

int lastMusicNumber = -1;

/// <summary>
/// Function for randomness of tracks
/// </summary>
/// <param name="music - ">Transmit music for loading and unloading tracks, as well as for switching tracks</param>
void PlayMusic(Music &music) {
	srand(time(0));
	int randomMusicNumber = rand() % 6;

	//Choice music
	if (randomMusicNumber == 0 && !IsMusicStreamPlaying(music) && randomMusicNumber != lastMusicNumber) {
		music = LoadMusicStream("Music\\mainMusic.mp3");
		if (GetMusicTimePlayed(music) < GetMusicTimeLength(music)) {
			PlayMusicStream(music);
		}
		lastMusicNumber = randomMusicNumber;
	}
	if (randomMusicNumber == 1 && !IsMusicStreamPlaying(music) && randomMusicNumber != lastMusicNumber) {
		music = LoadMusicStream("Music\\mainMusic_2.mp3");
		if ((GetMusicTimePlayed(music) < GetMusicTimeLength(music))) {
			PlayMusicStream(music);
		}
		lastMusicNumber = randomMusicNumber;
	}
	if (randomMusicNumber == 2 && !IsMusicStreamPlaying(music) && randomMusicNumber != lastMusicNumber) {
		music = LoadMusicStream("Music\\mainMusic_3.mp3");
		if (GetMusicTimePlayed(music) < GetMusicTimeLength(music)) {
			PlayMusicStream(music);
		}
		lastMusicNumber = randomMusicNumber;
	}
	if (randomMusicNumber == 3 && !IsMusicStreamPlaying(music) && randomMusicNumber != lastMusicNumber) {
		music = LoadMusicStream("Music\\mainMusic_4.mp3");
		if (GetMusicTimePlayed(music) < GetMusicTimeLength(music)) {
			PlayMusicStream(music);
		}
		lastMusicNumber = randomMusicNumber;
	}
	if (randomMusicNumber == 4 && !IsMusicStreamPlaying(music) && randomMusicNumber != lastMusicNumber) {
		music = LoadMusicStream("Music\\mainMusic_5.mp3");
		if (GetMusicTimePlayed(music) < GetMusicTimeLength(music)) {
			PlayMusicStream(music);
		}
		lastMusicNumber = randomMusicNumber;
	}
	if (randomMusicNumber == 5 && !IsMusicStreamPlaying(music) && randomMusicNumber != lastMusicNumber) {
		music = LoadMusicStream("Music\\mainMusic_6.mp3");
		if (GetMusicTimePlayed(music) < GetMusicTimeLength(music)) {
			PlayMusicStream(music);
		}
		lastMusicNumber = randomMusicNumber;
	}

	//How much did the song play
	float timePlayed = GetMusicTimePlayed(music) / (GetMusicTimeLength(music) - 1);

	if (timePlayed > 1.0f) {
		StopMusicStream(music);
		UnloadMusicStream(music);
		while (lastMusicNumber == randomMusicNumber) {
			randomMusicNumber = rand() % 6;
		}
	}
}

int main()
{
	setlocale(0, "ru");

	//Init window, audio and gui style
	InitWindow(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), "KVLT");
	InitAudioDevice();
	GuiLoadStyle("style_ui.rgs");

	SetTargetFPS(60);

	SetExitKey(KEY_NULL);

	//Variables for buttons
	bool exitRequest = false;
	bool playRequest = false;
	bool setRequest = false;

	//Text size and spacing changes
	Font font = LoadFont("Font.png");
	GuiSetFont(font);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
	GuiSetStyle(DEFAULT, TEXT_SPACING, 2);

	float volume = 50;

	float musicVolume = 0.1;
	Music playMusic = LoadMusicStream("");

	while (!GetExitWindow())
	{

		//Play, update and customization music
		PlayMusic(playMusic);
		if (IsMusicStreamPlaying(playMusic)) {
			UpdateMusicStream(playMusic);
		}

		//If the game is closed, a window pops up
		if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE) && !setRequest) {
			SetExitWindowRequest(true);
			exitRequest = true;
		}

		//Drawing display
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
		
		//Heading
		DrawTextEx(font, "KVLT", { 100 , 300 }, 92, 3, WHITE);

		//Buttons
		GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
		if (GuiButton({ 125, 500, 100, 40 }, "Play"))		playRequest = true;
		if (GuiButton({ 125, 575, 100, 40 }, "Settings"))	setRequest = true;
		if (GuiButton({ 125, 650, 100, 40 }, "Quit")) 		exitRequest = true;
		GuiSetStyle(DEFAULT, TEXT_SIZE, 16);

		//Play
		if (playRequest) {
		}

		//Open settings window
		if (setRequest) {
			int result = GuiWindowBox({600, 200, 800, 600}, "Settings");
			
			//Slider and master volume change
			DrawTextEx(font, "MasterVolume", { 650, 250 }, 20, 2, RAYWHITE);
			GuiSlider({ 650, 275, 100, 25 }, "", "100%", &volume, 0, 100);
			SetMasterVolume(volume);

			//Slider and musiv volume change
			DrawTextEx(font, "MusicVolume", { 650, 325 }, 20, 2, RAYWHITE);
			GuiSlider({ 650, 350, 100, 25 }, "", "100%", &musicVolume, 0, 1);
			SetMusicVolume(playMusic, musicVolume);

			//Exit frim settings
			if (result == 1) setRequest = false;
		}

		//Open exit window
		if (GetExitWindowRequest() || exitRequest && !setRequest) {
			int result = GuiMessageBox({(float)GetMonitorWidth(GetCurrentMonitor()) / 2 - 125, (float)GetMonitorHeight(GetCurrentMonitor()) / 2 - 50, 250, 100 },
				"#193#Quit?", "Are You Want To Quit?", "Yes;No");

			//Exit window choice
			if (result == 1) {
				SetExitWindow(true);
			}
			else if (result == 2 or result == 0) {
				SetExitWindowRequest(false);
				exitRequest = false;
			}
		}

		DrawTextEx(font, "develop. by SVTVN", { (float)GetMonitorWidth(GetCurrentMonitor()) / 2 - 150 , 1000 }, 36, 3, GRAY);
		EndDrawing();
	}

	//Close and unload
	UnloadMusicStream(playMusic);
	CloseWindow();
	CloseAudioDevice();

	return 0;
}

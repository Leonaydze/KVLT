#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <ctime>
#include "PlayerService.h"
#include "Altar.h"
#include "Ground.h"
#include "Border.h"

using json = nlohmann::json;
using namespace std;

bool PlayerOnGround(Player& player, Ground& ground) {
	player.SetPlayerCanJump(true);
	return (player.GetPlayerPositionX() + 88 >= ground.GetGroundPositionX() && player.GetPlayerPositionX() + 40 <= ground.GetGroundPositionX() + ground.GetGroundWidth()
		&& player.GetPlayerPositionY() + 128 >= ground.GetGroundPositionY() + 15 && player.GetPlayerPositionY() <= ground.GetGroundPositionY() + ground.GetGroundHeight());
}

void PlayerCantWalk(Player& player, Border& border) {
	if (player.GetPlayerPositionX() + 100 >= border.GetBorderPosX() && player.GetPlayerPositionX() + 100 <= border.GetBorderPosX() + 10 
		&& player.GetPlayerPositionY() + 131 >= border.GetBorderPosY() + 1) {
		player.SetPlayerCanWalk(-1);
		return;
	}
	if (player.GetPlayerPositionX() + 31 <= border.GetBorderPosX() + border.GetBorderWidth() && player.GetPlayerPositionX() + 31 >= border.GetBorderPosX() + border.GetBorderWidth() - 10 
		&& player.GetPlayerPositionY() + 131 >= border.GetBorderPosY() + 1) {
		player.SetPlayerCanWalk(1);
		return;
	}
	player.SetPlayerCanWalk(0);
}

double lastUpdateTime = 0;
/// <summary>
/// A function to indicate that the code is stopped for a while
/// </summary>
/// <param name="interval - "> The time for which the code will stop</param>
/// <returns></returns>
bool TriggerEvent(double interval) {
	double currentTime = GetTime();

	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;

		return true;
	}

	return false;
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

int lastMusicNumber = -1;

/// <summary>
/// Function for randomness of tracks
/// </summary>
/// <param name="music - ">Transmit music for loading and unloading tracks, as well as for switching tracks</param>
void PlayMusic(Music &music) {
	srand((unsigned)time(NULL));
	int randomMusicNumber = rand() % 7;

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
	if (randomMusicNumber == 6 && !IsMusicStreamPlaying(music) && randomMusicNumber != lastMusicNumber) {
		music = LoadMusicStream("Music\\mainMusic_7.mp3");
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
			randomMusicNumber = rand() % 7;
		}
	}
}

int main()
{
	setlocale(0, "ru");

	enum _gameScreen { mainMenu = 0, LVL_TUTORIAL, LVL_1, LVL_2, LVL_3, LVL_4 };
	_gameScreen _currentScreen = mainMenu;

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

	float musicVolume = 0.1f;
	Music playMusic = LoadMusicStream("");

	Player player;
	PlayerService playerS;

	player.Init(/*playerS.read()[0]*/);

	PlayerInventory playerInv;
	PlayerInventoryService playerInvS;

	PlayerWeapon playerW;
	PlayerWeaponService playerWS;

	Clergy c;
	PlayerClergyService cS;

	Ground mainGroundFloor = Ground({ { -1000 , 1000 } , 5400, 1500, DARKGRAY });
	Border mainBorder = Border({300, 700 }, WHITE, 20, 1000);

	Camera2D _playerCamera;

	_playerCamera.offset = { 1920.0f / 2.0f, 1080.0f / 2.0f };
	_playerCamera.zoom = 1.0f;
	_playerCamera.rotation = 0.0f;

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
		
		
		if(_currentScreen == mainMenu){
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
				_currentScreen = LVL_TUTORIAL;
			}

			//Open settings window
			if (setRequest) {
				int result = GuiWindowBox({ 600, 200, 800, 600 }, "Settings");

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
			DrawTextEx(font, "develop. by SVTVN", { (float)GetMonitorWidth(GetCurrentMonitor()) / 2 - 150 , 1000 }, 36, 3, GRAY);
		}
			//Open exit window
			if (GetExitWindowRequest() || exitRequest && !setRequest) {
				int result = GuiMessageBox({ (float)GetMonitorWidth(GetCurrentMonitor()) / 2 - 125, (float)GetMonitorHeight(GetCurrentMonitor()) / 2 - 50, 250, 100 },
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
		if (_currentScreen != mainMenu) {
			if (player.IsPlayerJump() && !player.PlayerMaxJump() && player.GetPlayerCanJump()) {
				player.MoveVertically();
			}
			else if (PlayerOnGround(player, mainGroundFloor)) {
				player.SetPlayerCanJump(true);
			}
			else if (player.PlayerMaxJump() || !player.IsPlayerJump()) {
				player.MoveVerticallyDown();
			}
			player.PlayerController();
			ClearBackground(BLACK);
			_playerCamera.target = { player.GetPlayerPositionX(), player.GetPlayerPositionY() - 200 };
			mainGroundFloor.GroundDraw();
			mainBorder.Draw();
			player.Draw();
			PlayerCantWalk(player, mainBorder);
		}

		EndDrawing();
		EndMode2D();
	}

	//Close and unload
	UnloadMusicStream(playMusic);
	CloseWindow();
	CloseAudioDevice();

	return 0;
}

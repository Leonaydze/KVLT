#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <ctime>
#include "PlayerService.h"
#include "Level_logic.h"

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
void PlayMusic(Music &music, bool& reroll) {
	srand((unsigned)time(NULL));
	int randomMusicNumber = rand() % 12;

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
	if (randomMusicNumber == 7 && !IsMusicStreamPlaying(music) && randomMusicNumber != lastMusicNumber) {
		music = LoadMusicStream("Music\\mainMusic_8.mp3");
		if (GetMusicTimePlayed(music) < GetMusicTimeLength(music)) {
			PlayMusicStream(music);
		}
		lastMusicNumber = randomMusicNumber;
	}
	if (randomMusicNumber == 8 && !IsMusicStreamPlaying(music) && randomMusicNumber != lastMusicNumber) {
		music = LoadMusicStream("Music\\mainMusic_9.mp3");
		if (GetMusicTimePlayed(music) < GetMusicTimeLength(music)) {
			PlayMusicStream(music);
		}
		lastMusicNumber = randomMusicNumber;
	}
	if (randomMusicNumber == 9 && !IsMusicStreamPlaying(music) && randomMusicNumber != lastMusicNumber) {
		music = LoadMusicStream("Music\\mainMusic_10.mp3");
		if (GetMusicTimePlayed(music) < GetMusicTimeLength(music)) {
			PlayMusicStream(music);
		}
		lastMusicNumber = randomMusicNumber;
	}
	if (randomMusicNumber == 10 && !IsMusicStreamPlaying(music) && randomMusicNumber != lastMusicNumber) {
		music = LoadMusicStream("Music\\mainMusic_11.mp3");
		if (GetMusicTimePlayed(music) < GetMusicTimeLength(music)) {
			PlayMusicStream(music);
		}
		lastMusicNumber = randomMusicNumber;
	}
	if (randomMusicNumber == 11 && !IsMusicStreamPlaying(music) && randomMusicNumber != lastMusicNumber) {
		music = LoadMusicStream("Music\\mainMusic_12.mp3");
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
			randomMusicNumber = rand() % 12;
		}
	}
	if (reroll) {
		StopMusicStream(music);
		UnloadMusicStream(music);
		while (lastMusicNumber == randomMusicNumber) {
			randomMusicNumber = rand() % 12;
		}
		reroll = false;
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
	bool setMusicReroll = false;

	Init();

	//Text size and spacing changes
	GuiSetFont(GetCurrentFont());
	GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
	GuiSetStyle(DEFAULT, TEXT_SPACING, 2);

	Sound playButton = LoadSound("Sounds\\Play_button.wav");

	float volume = 50;

	float musicVolume = 0.2f;
	Music playMusic = LoadMusicStream("");

	PlayerService playerS;

	Player player;
	player.Init(/*playerS.read()[0]*/);

	PlayerInventory playerInv;
	PlayerInventoryService playerInvS;

	PlayerWeapon playerW;
	PlayerWeaponService playerWS;

	Clergy c;
	PlayerClergyService cS;

	while (!GetExitWindow())
	{
		//Play, update and customization music
		PlayMusic(playMusic, setMusicReroll);
		SetMusicVolume(playMusic, musicVolume);
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

		if(GetCurrentGameScreen() == mainMenu) {
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
			//Heading
			DrawTextEx(GetCurrentFont(), "KVLT", { 100 , 300 }, 92, 3, WHITE);

			//Buttons
			GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
			if (GuiButton({ 125, 500, 100, 40 }, "Play"))		playRequest = true;
			if (GuiButton({ 125, 575, 100, 40 }, "Settings"))	setRequest = true;
			if (GuiButton({ 125, 650, 100, 40 }, "Quit")) 		exitRequest = true;
			GuiSetStyle(DEFAULT, TEXT_SIZE, 16);

			//Play
			if (playRequest) {
				PlaySound(playButton);
				SetCurrentScreen(LVL_TUTORIAL);
				playRequest = false;
				player.SetPlayerPositionV({ 0, 870 });
				setRequest = false;
			}

			//Open settings window
			if (setRequest) {
				int result = GuiWindowBox({ 600, 200, 800, 600 }, "Settings");

				//Slider and master volume change
				DrawTextEx(GetCurrentFont(), "MasterVolume", { 650, 250 }, 20, 2, RAYWHITE);
				GuiSlider({ 650, 275, 100, 25 }, "", "100%", &volume, 0, 100);
				GuiDrawIcon(ICON_AUDIO, 800, 280, 1, WHITE);
				SetMasterVolume(volume);

				//Slider and musiv volume change
				DrawTextEx(GetCurrentFont(), "MusicVolume", { 650, 325 }, 20, 2, RAYWHITE);
				GuiSlider({ 650, 350, 100, 25 }, "", "100%", &musicVolume, 0, 1);
				GuiDrawIcon(ICON_AUDIO, 800, 355, 1, WHITE);

				DrawTextEx(GetCurrentFont(), "Reroll track", { 650.0f, 410.0f }, 20, 2, RAYWHITE);
				if (GuiButton({ 800, 405, 30, 30 }, "#60#")) {
					setMusicReroll = true;
				}

				//Exit frim settings
				if (result == 1) setRequest = false;
			}
			DrawTextEx(GetCurrentFont(), "develop. by SVTVN", {(float)GetMonitorWidth(GetCurrentMonitor()) / 2 - 150 , 1000}, 36, 3, GRAY);
			//Open exit window
			if ((GetExitWindowRequest() || exitRequest) && !setRequest ) {
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
		}
		if (GetCurrentGameScreen() == LVL_TUTORIAL) {
			ClearBackground(BLACK);
			LEVEL_T_LOGIC(player);
			LEVEL_T_DRAW(player);
		}

		if (GetExitWindowRequest() && !setRequest  && GetCurrentGameScreen() != mainMenu) {
			int result = GuiMessageBox({ (float)player.GetPlayerPositionX() - 125, (float)player.GetPlayerPositionY() - 250, 300, 100},
				"#193#Quit?", "Quit to the main menu?(Y/N)", ";;;;;;;;;;;;;;;;;;;;");

			//Exit window choice
			if (result == 1 || IsKeyPressed(KEY_Y) || IsKeyPressed(KEY_ENTER)) {
				SetCurrentScreen(mainMenu);
				SetExitWindowRequest(false);
				exitRequest = false;
			}
			else if (result == 2 || result == 0 || IsKeyPressed(KEY_N)) {
				SetExitWindowRequest(false);
				exitRequest = false;
			}
		}

		EndDrawing();
		EndMode2D();
	}

	//Close and unload
	UnloadSound(playButton);
	UnloadMusicStream(playMusic);
	CloseWindow();
	CloseAudioDevice();

	return 0;
}

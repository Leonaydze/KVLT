#include <ctime>
#include "PlayerService.h"
#include "Level_logic.h"
#define RAYGUI_IMPLEMENTATION
#include "Clergy.h"
#include <raygui.h>

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

	Clergy _playerClergy = Clergy();
	_playerClergy.Init();

	PlayerInventory playerInv;
	playerInv.Init();

	PlayerInventoryService playerInvS;

	PlayerWeapon playerW;
	PlayerWeaponService playerWS;

	Clergy c;
	PlayerClergyService cS;

	_gameScreen lastScreen = GetCurrentGameScreen();

	unsigned short int hpLvl = player.GetHealthLevel();
	unsigned short int dashLvl = player.GetDashLevel();
	unsigned short int staminaLvl = player.GetStaminaLevel();

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
			DrawTextEx(GetCurrentFont(), "KVLT", { (float)100 , (float)300 }, 92, 3, WHITE);

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
				lastScreen = LVL_TUTORIAL;
				playRequest = false;
				player.SetPlayerPositionV({ 0.0f, 870.0f });
				setRequest = false;
			}

			//Open settings window
			if (setRequest) {
				int result = GuiWindowBox({ 600.0f, 200.0f, 800.0f, 600.0f }, "Settings");

				//Slider and master volume change
				DrawTextEx(GetCurrentFont(), "MasterVolume", { 650.0f, 250.0f }, 20, 2, RAYWHITE);
				GuiSlider({ 650.0f, 275.0f, 100.0f, 25.0f }, "", "100%", &volume, 0, 100);
				GuiDrawIcon(ICON_AUDIO, 800, 280, 1, WHITE);
				SetMasterVolume(volume);

				//Slider and musiv volume change
				DrawTextEx(GetCurrentFont(), "MusicVolume", { 650.0f, 325.0f }, 20, 2, RAYWHITE);
				GuiSlider({ 650.0f, 350.0f, 100.0f, 25.0f }, "", "100%", &musicVolume, 0, 1);
				GuiDrawIcon(ICON_AUDIO, 800, 355, 1, WHITE);

				DrawTextEx(GetCurrentFont(), "Reroll track", { 650.0f, 410.0f }, 20, 2, RAYWHITE);
				if (GuiButton({ 800.0f, 405.0f, 30.0f, 30.0f }, "#60#")) setMusicReroll = true;

				//Exit frim settings
				if (result == 1 || IsKeyPressed(KEY_ESCAPE)) setRequest = false;
			}
			DrawTextEx(GetCurrentFont(), "develop. by SVTVN", {(float)GetMonitorWidth(GetCurrentMonitor()) / (float)2 - 150.0f , 1000.0f }, 36, 3, GRAY);

			//Open exit window
			if ((GetExitWindowRequest() || exitRequest) && !setRequest ) {
				int result = GuiMessageBox({ (float)GetMonitorWidth(GetCurrentMonitor()) / (float)2 - 125.0f, (float)GetMonitorHeight(GetCurrentMonitor()) / 2 - 50.0f, 250.0f, 100.0f },
					"#193#Quit?", "Are You Want To Quit?", "Yes;No");

				//Exit window choice
				if (result == 1) {
					SetExitWindow(true);
				}
				else if (result == 2 || result == 0) {
					SetExitWindowRequest(false);
					exitRequest = false;
				}
			}
		}

		if (GetCurrentGameScreen() == LVL_TUTORIAL) {
			ClearBackground(BLACK);
			LEVEL_T_DRAW(player);
			LEVEL_T_LOGIC(player);
			_playerClergy.Draw(player, GetCurrentFont());
			playerInv.Draw(player, GetCurrentFont());
			playerInv.HealFlask(player);
		}

		unsigned short int neededClergy = (hpLvl + dashLvl + staminaLvl) * 10;

		if (GetCurrentGameScreen() == UpgradeLevels) {
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
			int result = GuiWindowBox({ 460.0f, 140.0f, 1000.0f, 800.0f }, "Stats");

			DrawTextEx(GetCurrentFont(), "HP LEVEL", { 500.0f, 200.0f }, 25, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Current health level: %i", hpLvl), { 500.0f, 240.0f }, 20, 2, RAYWHITE);
			if (GuiButton({ 700.0f, 260.0f, 24.0f, 24.0f }, "->") && hpLvl < 5) {
				hpLvl++;
			}
			else if (GuiButton({ 500.0f, 260.0f, 24.0f, 24.0f }, "<-") && hpLvl > 0 && hpLvl != 5 && player.GetMaxPlayerHealth() / 10 % 10 < hpLvl ) {
				hpLvl--;
			}
			DrawTextEx(GetCurrentFont(), TextFormat("Current health: %i", player.GetMaxPlayerHealth()), { 500.0f, 350.0f }, 20, 2, WHITE);
			if (player.GetMaxPlayerHealth() / 10 % 10 < hpLvl && player.GetMaxPlayerHealth() / 10 % 10 != hpLvl) {
				DrawTextEx(GetCurrentFont(), TextFormat("Updated health: %i", player.GetMaxPlayerHealth() + hpLvl * 10), { 500.0f, 400.0f }, 20, 2, RAYWHITE);
			}
			else {
				DrawTextEx(GetCurrentFont(), TextFormat("Updated health: %i", player.GetMaxPlayerHealth()), { 500.0f, 400.0f }, 20, 2, RAYWHITE);
			}

			DrawTextEx(GetCurrentFont(), "DASH DISTANCE", { 800.0f, 200.0f }, 25, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Current dash level: %i", dashLvl), { 800.0f, 240.0f }, 20, 2, RAYWHITE);
			if (GuiButton({ 1000.0f, 260.0f, 24.0f, 24.0f }, "->") && dashLvl < 5) {
				dashLvl++;
			}
			else if (GuiButton({ 800.0f, 260.0f, 24.0f, 24.0f }, "<-") && dashLvl > 0 && dashLvl != 5 && player.GetDashLevel() < dashLvl) {
				dashLvl--;
			}
			DrawTextEx(GetCurrentFont(), TextFormat("Current dash: %i", player.GetDashLevel()), { 800.0f, 350.0f }, 20, 2, WHITE);
			if (player.GetDashLevel() != dashLvl && player.GetDashLevel() < dashLvl) {
				DrawTextEx(GetCurrentFont(), TextFormat("Updated dash: %i", player.GetDashLevel() + dashLvl), { 800.0f, 400.0f }, 20, 2, RAYWHITE);
			}
			else {
				DrawTextEx(GetCurrentFont(), TextFormat("Updated dash: %i", player.GetDashLevel()), { 800.0f, 400.0f }, 20, 2, RAYWHITE);
			}

			DrawTextEx(GetCurrentFont(), "STAMINA LEVEL", { 1100.0f, 200.0f }, 25, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Current stamina level: %i", staminaLvl), { 1100.0f, 240.0f }, 20, 2, RAYWHITE);
			if (GuiButton({ 1300.0f, 260.0f, 24.0f, 24.0f }, "->") && staminaLvl < 4) {
				staminaLvl++;
			}
			else if (GuiButton({ 1100.0f, 260.0f, 24.0f, 24.0f }, "<-") && staminaLvl > 0 && staminaLvl != 4 && player.GetMaxPlayerHealth() / 10 % 10 < hpLvl) {
				staminaLvl--;
			}
			DrawTextEx(GetCurrentFont(), TextFormat("Current stamina: %i", player.GetStaminaLevel()), { 1100.0f, 350.0f }, 20, 2, WHITE);
			if (player.GetStaminaLevel() < staminaLvl && player.GetStaminaLevel() != staminaLvl) {
				DrawTextEx(GetCurrentFont(), TextFormat("Updated stamina: %i", player.GetStaminaLevel() + staminaLvl), { 1100.0f, 400.0f }, 20, 2, RAYWHITE);
			}
			else{
				DrawTextEx(GetCurrentFont(), TextFormat("Updated stamina: %i", player.GetStaminaLevel()), { 1100.0f, 400.0f }, 20, 2, RAYWHITE);
			}

			if (GuiButton({1300.0f, 850.0f, 80.0f, 40.0f },"Accept") && neededClergy <= _playerClergy.GetClergyCount() ) {
				player.UpgradeDashLevel(dashLvl);
				player.UpgradeHealthLevel(hpLvl);
				player.UpgradeStaminaLevel(staminaLvl);
				player.SetPlayerPositionV(GetLastPlayerPosition());
				_playerClergy.TakeOffClergy(neededClergy);
				SetCurrentScreen(lastScreen);
			}

			DrawTextEx(GetCurrentFont(), TextFormat("Needed Clergy: %i", neededClergy), { 500.0f, 840.0f}, 20, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("You have Clergy: %i", _playerClergy.GetClergyCount()), {500.0f, 880.0f}, 20, 2, RAYWHITE);

			if (result == 1 || IsKeyPressed(KEY_ESCAPE)) { 
				player.SetPlayerPositionV(GetLastPlayerPosition());
				SetCurrentScreen(lastScreen); 
			}
		}

		if (GetExitWindowRequest() && !setRequest  && GetCurrentGameScreen() != mainMenu && GetCurrentGameScreen() != UpgradeLevels) {
			int result = GuiMessageBox({ (float)player.GetPlayerPositionX() - 125.0f, (float)player.GetPlayerPositionY() - 250.0f, 300.0f, 100.0f },
				"#193#Quit?", "Quit to the main menu?(Y/N)", ";;;;;;;;;;;;;;;;;;;;");

			//Exit window choice
			if (IsKeyPressed(KEY_Y) || IsKeyPressed(KEY_ENTER)) {
				SetCurrentScreen(mainMenu);
				SetExitWindowRequest(false);
				exitRequest = false;
			}
			else if (IsKeyPressed(KEY_N)) {
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

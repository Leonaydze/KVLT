﻿#include <ctime>
#include "PlayerService.h"
#include "Level_logic.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include "Clergy.h"
#include "Vampire.h"

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
	srand(static_cast<unsigned>(time(NULL)));
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
	PlayerWeaponService playerWS;
	PlayerClergyService clergyS;
	PlayerInventoryService playerInvS;

	Player player;
	try {
		player.Init(playerS.read());
	}
	catch (...) {
		playerS.create(player);
	}

	Clergy _playerClergy = Clergy();
	try {
		_playerClergy.Init(clergyS.read());
	}
	catch (...) {
		clergyS.create(_playerClergy);
	}

	PlayerInventory playerInv;
	try {
		playerInv.Init(playerInvS.read());
	}
	catch (...) {
		playerInvS.create(playerInv);
	}

	PlayerWeapon playerW = PlayerWeapon();
	try {
		playerW.Init(playerWS.read());
	}
	catch (...) {
		playerWS.create(playerW);
	}

	unsigned short int hpLvl = player.GetHealthLevel();
	unsigned short int dashLvl = player.GetDashLevel();
	unsigned short int staminaLvl = player.GetStaminaLevel();

	Sound _inventorySound = LoadSound("Sounds\\Inventory_sound.mp3");

	while (!GetExitWindow())
	{	
		//Play, update and customization music
		PlayMusic(playMusic, setMusicReroll);
		SetMusicVolume(playMusic, musicVolume);
		if (IsMusicStreamPlaying(playMusic)) {
			UpdateMusicStream(playMusic);
		}

		//If the game is closed, a window pops up
		if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE) && !setRequest && GetCurrentGameScreen() != UpgradeLevels 
			&& GetCurrentGameScreen() != Inventory && GetCurrentGameScreen() != DEATH_SCREEN) {
			SetExitWindowRequest(true);
			exitRequest = true;
		}

		//Drawing display
		BeginDrawing();

		if(GetCurrentGameScreen() == mainMenu) {
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
			//Heading
			DrawTextEx(GetCurrentFont(), "KVLT", { static_cast <float>(100) , static_cast <float>(300) }, 92, 3, WHITE);

			//Buttons
			GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
			if (GuiButton({ 125.0f, 500.0f, 100.0f, 40.0f }, "Play"))		playRequest = true;
			if (GuiButton({ 125.0f, 575.0f, 100.0f, 40.0f }, "Settings"))	setRequest = true;
			if (GuiButton({ 125.0f, 650.0f, 100.0f, 40.0f }, "Quit")) 		exitRequest = true;
			GuiSetStyle(DEFAULT, TEXT_SIZE, 16);

			//Play
			if (playRequest) {
				PlaySound(playButton);
				StopSound(player._jump);
				
				if (WhereWasPlayer(player)) {
					playRequest = false;
					setRequest = false;
				}
				else {
					SetCurrentScreen(LVL_TUTORIAL);
					SetLastGameScreen(LVL_TUTORIAL);

					playRequest = false;
					setRequest = false;
					//player.SetPlayerPositionV({ 0.0f, 870.0f });
				}
			}

			//Open settings window
			if (setRequest) {
				int result = GuiWindowBox({ 600.0f, 200.0f, 800.0f, 600.0f }, "#141# Settings");

				//Slider and master volume change
				DrawTextEx(GetCurrentFont(), "MasterVolume", { 650.0f, 250.0f }, 20, 2, RAYWHITE);
				GuiSlider({ 650.0f, 275.0f, 100.0f, 25.0f }, "", "100%", &volume, 0, 100);
				GuiDrawIcon(ICON_AUDIO, 800, 280, 1, WHITE);
				SetMasterVolume(volume);

				//Slider and music volume change
				DrawTextEx(GetCurrentFont(), "MusicVolume", { 650.0f, 325.0f }, 20, 2, RAYWHITE);
				GuiSlider({ 650.0f, 350.0f, 100.0f, 25.0f }, "", "100%", &musicVolume, 0, 1);
				GuiDrawIcon(ICON_AUDIO, 800, 355, 1, WHITE);

				DrawTextEx(GetCurrentFont(), "Reroll track", { 650.0f, 410.0f }, 20, 2, RAYWHITE);
				if (GuiButton({ 800.0f, 405.0f, 30.0f, 30.0f }, "#60#")) setMusicReroll = true;

				DrawTextEx(GetCurrentFont(), "Delete Save", { 650.0f, 465.0f }, 20, 2, RAYWHITE);
				if (GuiButton({ 800.0f, 460.0f, 30.0f, 30.0f }, "#60#")) {
					remove("Save\\PlayerClergyData.json");
					remove("Save\\PlayerData.json");
					remove("Save\\PlayerInventoryData.json");
					remove("Save\\PlayerWeaponData.json");
					hpLvl = 0;
					staminaLvl = 0;
					dashLvl = 0;
					player.Init(Player());
					_playerClergy.Init(Clergy());
					playerInv.Init(PlayerInventory());
					playerW.Init(PlayerWeapon());
					Restart();
				}

				//Exit frim settings
				if (result == 1 || IsKeyPressed(KEY_ESCAPE)) setRequest = false;
			}
			DrawTextEx(GetCurrentFont(), "develop. by SVTVN", {static_cast<float>(GetMonitorWidth(GetCurrentMonitor()) / 2 - 150) , 1000.0f }, 36, 3, GRAY);

			//Open exit window
			if ((GetExitWindowRequest() || exitRequest) && !setRequest ) {
				int result = GuiMessageBox({ static_cast<float>(GetMonitorWidth(GetCurrentMonitor()) / 2 - 125), static_cast<float>(GetMonitorHeight(GetCurrentMonitor()) / 2 - 50), 250.0f, 100.0f },
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

		unsigned short int neededClergy = (hpLvl + dashLvl + staminaLvl) * 10;
		if (GetCurrentGameScreen() == UpgradeLevels) {
			StopSound(player._jump);
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
			int result = GuiWindowBox({ 460.0f, 140.0f, 1000.0f, 800.0f }, "#148# Stats");

			DrawTextEx(GetCurrentFont(), "HP LEVEL", { 500.0f, 200.0f }, 25, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Current health level: %i", hpLvl), { 500.0f, 240.0f }, 20, 2, RAYWHITE);
			if (GuiButton({ 700.0f, 280.0f, 24.0f, 24.0f }, "->") && hpLvl < 5) {
				hpLvl++;
			}
			else if (GuiButton({ 500.0f, 280.0f, 24.0f, 24.0f }, "<-") && hpLvl > 0 && player.GetMaxPlayerHealth() / 10 % 10 < hpLvl ) {
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
			if (GuiButton({ 990.0f, 280.0f, 24.0f, 24.0f }, "->") && dashLvl < 5) {
				dashLvl++;
			}
			else if (GuiButton({ 800.0f, 280.0f, 24.0f, 24.0f }, "<-") && dashLvl > 0 && dashLvl != 5 && player.GetDashLevel() < dashLvl) {
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
			if (GuiButton({ 1320.0f, 280.0f, 24.0f, 24.0f }, "->") && staminaLvl < 4) {
				staminaLvl++;
			}
			else if (GuiButton({ 1100.0f, 280.0f, 24.0f, 24.0f }, "<-") && staminaLvl > 0 && player.GetStaminaLevel() < staminaLvl) {
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
				SetCurrentScreen(GetLastGameScreen());
			}

			DrawTextEx(GetCurrentFont(), TextFormat("Needed Clergy: %i", neededClergy), { 500.0f, 840.0f}, 20, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("You have Clergy: %i", _playerClergy.GetClergyCount()), {500.0f, 880.0f}, 20, 2, RAYWHITE);

			if (result == 1 || IsKeyPressed(KEY_ESCAPE)) { 
				hpLvl = player.GetHealthLevel();
				dashLvl = player.GetDashLevel();
				staminaLvl = player.GetStaminaLevel();
				player.SetPlayerPositionV(GetLastPlayerPosition());
				SetCurrentScreen(GetLastGameScreen()); 
			}
		}
		
		if (GetCurrentGameScreen() == Inventory) {
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
			int result = GuiWindowBox({ 460.0f, 140.0f, 1000.0f, 800.0f }, "#157# Player Inventory");

			DrawTextEx(GetCurrentFont(), "CURRENT HP", { 500.0f, 200.0f }, 25, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Max health: %i", player.GetMaxPlayerHealth()), { 500.0f, 240.0f }, 20, 2, RAYWHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Current health: %i", player.GetPlayerHealth()), { 500.0f, 270.0f }, 20, 2, RAYWHITE);

			DrawTextEx(GetCurrentFont(), "CURRENT DASH DISTANCE", { 500.0f, 330.0f }, 25, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Current dash level: %i", 100 + player.GetDashLevel() * 10), { 500.0f, 370.0f }, 20, 2, RAYWHITE);

			DrawTextEx(GetCurrentFont(), "CURRENT STAMINA", { 500.0f, 430.0f }, 25, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Max stamina charges: %i", player.GetStaminaLevel() + 4), { 500.0f, 470.0f }, 20, 2, RAYWHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Current stamina charges: %i", player.GetCurrentStamina()), { 500.0f, 500.0f }, 20, 2, RAYWHITE);

			DrawTextEx(GetCurrentFont(), "WEAPON WEIGHT", { 500.0f, 600.0f }, 25, 2, WHITE);
			if (playerW.GetCurrentWeight() == 0) {
				DrawTextEx(GetCurrentFont(), "Current weapon weight: Light", { 500.0f, 640.0f }, 20, 2, RAYWHITE);
			}
			if (playerW.GetCurrentWeight() == 1) {
				DrawTextEx(GetCurrentFont(), "Current weapon weight: Medium", { 500.0f, 640.0f }, 20, 2, RAYWHITE);
			}
			if (playerW.GetCurrentWeight() == 2) {
				DrawTextEx(GetCurrentFont(), "Current weapon weight: Heavy", { 500.0f, 640.0f }, 20, 2, RAYWHITE);
			}

			DrawTextEx(GetCurrentFont(), "WEAPON DAMAGE", { 500.0f, 700.0f }, 25, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Current weapon damage: %i", playerW.GetWeaponDamage()), { 500.0f, 740.0f }, 20, 2, RAYWHITE);

			DrawTextEx(GetCurrentFont(), "WEAPON SPEED ATTACK", { 500.0f, 800.0f }, 25, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Current weapon speed attack: %01.01f", playerW.GetWeaponSpeed()), { 500.0f, 840.0f }, 20, 2, RAYWHITE);

			//right column
			DrawTextEx(GetCurrentFont(), "FLASK COUNT", { 1000.0f, 200.0f }, 25, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Current flask count: %i", playerInv.GetCurrentCountFlask()), { 1000.0f, 240.0f }, 20, 2, RAYWHITE);

			DrawTextEx(GetCurrentFont(), "FLASK HEAL", { 1000.0f, 300.0f }, 25, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Current flask count: %i", playerInv.GetFlaskHeal()), { 1000.0f, 340.0f }, 20, 2, RAYWHITE);

			DrawTextEx(GetCurrentFont(), "CLERGY COUNT", { 1000.0f, 400.0f }, 25, 2, WHITE);
			DrawTextEx(GetCurrentFont(), TextFormat("Current clergy count: %i", _playerClergy.GetClergyCount()), { 1000.0f, 440.0f }, 20, 2, RAYWHITE);

			if (result == 1 || IsKeyPressed(KEY_ESCAPE)) {
				player.SetPlayerPositionV(GetLastPlayerPosition());
				SetCurrentScreen(GetLastGameScreen());
			}
		}

		if (IsKeyDown(KEY_TAB) && GetCurrentGameScreen() != Inventory && GetCurrentGameScreen() != mainMenu && GetCurrentGameScreen() != UpgradeLevels && GetCurrentGameScreen() != DEATH_SCREEN) {
			StopSound(player._jump);
			SetLastGameScreen(GetCurrentGameScreen());
			SetLastPlayerPosition(player.GetPlayerPositionV());
			SetCurrentScreen(Inventory);
			PlaySound(_inventorySound);
		}

		if (GetCurrentGameScreen() == LVL_TUTORIAL) {
			ClearBackground(BLACK);
			LEVEL_T_DRAW(player);
			LEVEL_T_LOGIC(player, playerW);
			_playerClergy.Draw(player, GetCurrentFont());
			playerInv.Draw(player, GetCurrentFont());
			playerInv.HealFlask(player);
		}

		if (GetExitWindowRequest() && !setRequest  && GetCurrentGameScreen() != mainMenu && GetCurrentGameScreen() != UpgradeLevels && GetCurrentGameScreen() != Inventory && GetCurrentGameScreen() != DEATH_SCREEN) {
			int result = GuiMessageBox({ static_cast<float>(player.GetPlayerPositionX()) - 125.0f, static_cast<float>(player.GetPlayerPositionY()) - 250.0f, 300.0f, 100.0f },
				"#193#Quit?", "Quit to the main menu?(Y/N)", ";;;;;;;;;;;;;;;;;;;;");
			StopSound(player._jump);

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

		if (GetCurrentGameScreen() == DEATH_SCREEN) {
			ClearBackground(BLACK);
			DEATH_SCREEN_DRAW(player);
		}

		if (GetLastGameScreen() != GetCurrentGameScreen() && GetCurrentGameScreen() != mainMenu && GetCurrentGameScreen() != UpgradeLevels 
			&& GetCurrentGameScreen() != Inventory && GetCurrentGameScreen() != DEATH_SCREEN) {
			SetLastGameScreen(GetCurrentGameScreen());
		}

		EndDrawing();
		EndMode2D();
	}

	playerWS.create(playerW);
	playerInvS.create(playerInv);
	clergyS.create(_playerClergy);
	playerS.create(player);

	//Close and unload
	UnloadSound(playButton);
	UnloadMusicStream(playMusic);
	CloseWindow();
	CloseAudioDevice();

	return 0;
}
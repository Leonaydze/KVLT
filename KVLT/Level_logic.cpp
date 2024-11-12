#include "Level_logic.h"

extern 	_gameScreen _currentScreen = mainMenu;

double _lastUpdateTime = (double)0;
/// <summary>
/// A function to indicate that the code is stopped for a while
/// </summary>
/// <param name="interval - "> The time for which the code will stop</param>
/// <returns></returns>
bool TriggerEvent(float interval) {
	float currentTime = (float)GetTime();

	if (currentTime - _lastUpdateTime >= interval) {
		_lastUpdateTime = currentTime;

		return true;
	}

	return false;
}

_gameScreen GetCurrentGameScreen()
{
	return _currentScreen;
}

void SetCurrentScreen(_gameScreen curScreen)
{ 
	_currentScreen = curScreen;
}

Vector2 _lastPlayerPosition;

Vector2 GetLastPlayerPosition() {
	return _lastPlayerPosition;
}

void SetLastPlayerPosition(Vector2 lastPlayerPosition) {
	_lastPlayerPosition = lastPlayerPosition;
}

extern Font font = LoadFont("");

Priest priest = Priest({ 2900, 910 });

void Init()
{
	font = LoadFont("Font.png");;
	priest.Init();
}

Font GetCurrentFont()
{
	return font;
}

template <typename T>
void EnemyAttacksThePlayer(T& enemy, Player& player) {
	if (player.GetPlayerHealth() > 0 && player.GetPlayerPositionX() + 128 >= enemy.GetEnemyPosX() - 100
		&& player.GetPlayerPositionX() <= enemy.GetEnemyPosX() + 232
		&& player.GetPlayerPositionY() >= enemy.GetEnemyPosY() - 90
		&& player.GetPlayerPositionY() + 198 <= enemy.GetEnemyPosY() + 222 && enemy.GetEnemyHealth() > 0) {
		if (EventTriggered(enemy.GetEnemyAttackSpeed)) {
			player.PlayerTakesDamage(enemy.GetEnemyDamage());
		}
	}
}

template <typename T>
void PlayerAttacksEnemy(T& enemy, Player& player, PlayerWeapon& pw) {
	if (player.GetPlayerHealth() > 0 && player.GetPlayerPositionX() + 128 >= enemy.GetEnemyPositionX() - 80
		&& player.GetPlayerPositionX() <= enemy.GetEnemyPositionX() + 212
		&& player.GetPlayerPositionY() >= enemy.GetEnemyPositionY() - 80
		&& player.GetPlayerPositionY() + 128 <= enemy.GetEnemyPositionY() + 212) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && EventTriggered(pw.GetWeaponSpeed())) {
			enemy.EnemyGetDamage(pw.GetWeaponDamage());
			RandomizePlayerAttack();
		}
	}
}

template <typename T>
void EnemyGoesToThePlayer(T& enemy, Player& player) {
	if (player.GetPlayerPositionX() + 128 >= enemy.GetEnemyPosX() - 250
		&& player.GetPlayerPositionX() + 128 <= enemy.GetEnemyPosX() + 128 && enemy.GetEnemyHealth() > 0) {
		enemy.EnemyMoveX(-5.5f);
	}
	if (player.GetPlayerPositionX() + 128 <= enemy.GetEnemyPosX() + 378
		&& player.GetPlayerPositionX() >= enemy.GetEnemyPosX() && enemy.GetEnemyHealth() > 0) {
		enemy.EnemyMoveX(5.5f);
	}
}

template <typename T>
bool EnemyOnGround(T& enemy, Ground& ground) {
	return (enemy.GetEnemyPosX() + 80 >= ground.GetGroundPositionX() && enemy.GetEnemyPosX() <= ground.GetGroundPositionX() + ground.GetGroundWidth()
		&& enemy.GetEnemyPosY() + 132 >= ground.GetGroundPositionY() + 15 && enemy.GetEnemyPosY() <= ground.GetGroundPositionY() + ground.GetGroundHeight());
}

bool PlayerOnGround(Player& player, Ground& ground) {
	return (player.GetPlayerPositionX() + 88 >= ground.GetGroundPositionX() && player.GetPlayerPositionX() + 40 <= ground.GetGroundPositionX() + ground.GetGroundWidth()
		&& player.GetPlayerPositionY() + 128 >= ground.GetGroundPositionY() + 15 && player.GetPlayerPositionY() + 108 <= ground.GetGroundPositionY() + ground.GetGroundHeight());
}

bool PlayerCantWalk(Player& player, Border& border) {
	if (player.GetPlayerPositionX() + 120 >= border.GetBorderPosX() && player.GetPlayerPositionX() + 120 <= border.GetBorderPosX() + 10
		&& player.GetPlayerPositionY() + 131 >= border.GetBorderPosY() + 1 && player.GetPlayerPositionY() <= border.GetBorderPosY() + border.GetBorderHeight() - 1) {
		player.SetPlayerCanWalk(-1);
		return true;
	}
	if (player.GetPlayerPositionX() + 21 <= border.GetBorderPosX() + border.GetBorderWidth() && player.GetPlayerPositionX() + 21 >= border.GetBorderPosX() + border.GetBorderWidth() - 10
		&& player.GetPlayerPositionY() + 131 >= border.GetBorderPosY() + 1 && player.GetPlayerPositionY() <= border.GetBorderPosY() + border.GetBorderHeight() - 1) {
		player.SetPlayerCanWalk(1);
		return true;
	}
	if (player.GetPlayerPositionX() + 120 >= border.GetBorderPosX() + 20 && player.GetPlayerPositionX() + 64 <= border.GetBorderPosX() + border.GetBorderWidth() / 2
		&& player.GetPlayerPositionY() + 128 >= border.GetBorderPosY() + 30 && player.GetPlayerPositionY() <= border.GetBorderPosY() + border.GetBorderHeight() - 20) {
		player.SetPlayerPositionX((float)border.GetBorderPosX() - (float)130);
		return true;
	}
	if (player.GetPlayerPositionX() + 11 <= border.GetBorderPosX() + border.GetBorderWidth() - 20 && player.GetPlayerPositionX()  + 64 >= border.GetBorderPosX() + border.GetBorderWidth() / 2
		&& player.GetPlayerPositionY() + 128 >= border.GetBorderPosY() + 30 && player.GetPlayerPositionY() <= border.GetBorderPosY() + border.GetBorderHeight() - 20) {
		player.SetPlayerPositionX((float)border.GetBorderPosX() + (float)border.GetBorderWidth() + (float)5);
		return true;
	}
	player.SetPlayerCanWalk(0);
	return false;
}

void ResurrectionPlayer(Player& player, Altar& altar) {
	if (player.PlayerDeath() && altar.GetPlayerWasAtAltar()) {
		player.SetPlayerPositionV(altar.GetAltarPosV());
		player.SetPlayerHealth(player.GetMaxPlayerHealth() / 2);
	}
	else if(player.PlayerDeath()) {
		SetCurrentScreen(mainMenu);
		player.Nullification();
	}
}


template<typename T>
bool PlayerCanTalkWithNpc(Player& player, T& other) {
	return (player.GetPlayerPositionX() + 128 >= other.GetNpcPosX() - 40 && player.GetPlayerPositionX() <= other.GetNpcPosX() + 168
		&& player.GetPlayerPositionY() + 20 >= other.GetNpcPosY() - 20 && player.GetPlayerPositionY() + 108 <= other.GetNpcPosY() + 148);
}
bool UpgradePlayerLevel(Player& player, Priest& priest) {
	if (IsKeyPressed(KEY_E) && PlayerCanTalkWithNpc(player, priest) && !priest.NpcDeath() && !player.PlayerDeath()) {
		SetLastPlayerPosition(player.GetPlayerPositionV());
		_currentScreen = UpgradeLevels;
		return true;
	}
	return false;
}

Camera2D _playerCamera;

Ground mainGroundFloor = Ground({ { -1000.0f , 1000.0f } , 14400, 1500, DARKGRAY });

//Border  = Border({ 500, 800 }, RAYWHITE, 40, 1000);
Ground _firstG = Ground({ 500.0f, 875.0f }, 150, 30, RAYWHITE);
Ground _secondG = Ground({850.0f, 750.0f }, 150, 30, RAYWHITE);

Border _border = Border({ 1200.0f, 650.0f }, 1000, 150,  DARKGRAY);
Ground _borderG = Ground({ 1200.0f, 650.0f }, 150, 20, DARKGRAY);

Border _groundBorder = Border({ 1349.0f, 650.0f }, 50, 450, DARKBROWN);
Border _border2 = Border({ 1798.0f, -600.0f }, 1300, 810, DARKGRAY);

Border _borderAlt = Border({ 2600.0f, -300.0f }, 3000, 40, DARKGRAY);

void LEVEL_T_LOGIC(Player& player) {
	if (!UpgradePlayerLevel(player, priest)) {
		player.PlayerController();
	}
	if (player.IsPlayerJump() && !player.PlayerMaxJump() && player.GetPlayerCanJump()) {
		player.MoveVertically();
	}
	else if (PlayerOnGround(player, mainGroundFloor) || PlayerOnGround(player, _firstG) || PlayerOnGround(player, _secondG) 
		|| PlayerOnGround(player, _borderG)) {
		player.SetPlayerCanJump(true);
		PlaySound(player._jump);
	}
	else if (player.PlayerMaxJump() || !player.IsPlayerJump()) {
		player.SetPlayerCanJump(false);
		player.MoveVerticallyDown();
	}

	if (PlayerCantWalk(player, _border)) {
		PlayerCantWalk(player, _border);
	}
	else if (PlayerCantWalk(player, _border2)) {
		PlayerCantWalk(player, _border2);
	}
	else if (PlayerCantWalk(player, _borderAlt)) {
		PlayerCantWalk(player, _borderAlt);
	}
}

void LEVEL_T_DRAW(Player& player) {
	BeginMode2D(_playerCamera);

	_playerCamera.target = { player.GetPlayerPositionX(), player.GetPlayerPositionY() - 200 };
	_playerCamera.offset = { 1920.0f / 2.0f, 1080.0f / 2.0f };
	_playerCamera.zoom = 1.0f;
	_playerCamera.rotation = 0.0f;

	DrawTextEx(font, "PRESS WASD TO MOVE", {-200.0f, 700.0f }, 30, 3, RAYWHITE);
	DrawTextEx(font, "PRESS SHIFT TO MOVE FASTER", { -270.0f, 730.0f }, 30, 3, RAYWHITE);

	DrawTextEx(font, "PRESS SPACE TO JUMP", {400.0f, 700.0f }, 30, 3, RAYWHITE);

	DrawTextEx(font, "JUMP DOWN", { 1485.0f, 500.0f }, 30, 3, RAYWHITE);

	DrawTextEx(font, "PUSH ALT TO DASH", { 2250.0f, 800.0f }, 30, 3, RAYWHITE);
	DrawTextEx(font, "(come close)", { 2300.0f, 830.0f }, 30, 3, RAYWHITE);

	_firstG.GroundDraw();
	_secondG.GroundDraw();

	_groundBorder.Draw();
	_border.Draw();

	_border2.Draw();

	_borderAlt.Draw();

	mainGroundFloor.GroundDraw();

	player.Draw();

	priest.Draw();

	if (PlayerCanTalkWithNpc(player, priest)) {
		DrawTextEx(font, "PRESS E TO TALK", { priest.GetNpcPosX() - 70.0f, priest.GetNpcPosY() - 100.0f }, 30, 2, RAYWHITE);
	}
}
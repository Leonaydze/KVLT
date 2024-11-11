#include "Level_logic.h"
#include "Priest.h"

extern 	_gameScreen _currentScreen = mainMenu;

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
	if (player.PlayerDeath()) {
		player.SetPlayerPositionV(altar.GetAltarPosV());
		player.SetPlayerHealth(player.GetMaxPlayerHealth() / 2);
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
	_playerCamera.target = { player.GetPlayerPositionX(), player.GetPlayerPositionY() - 200 };
	_playerCamera.offset = { 1920.0f / 2.0f, 1080.0f / 2.0f };
	_playerCamera.zoom = 1.0f;
	_playerCamera.rotation = 0.0f;

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
		DrawTextEx(font, "PRESS E TO TALK", { priest.GetNpcPosX() - 70.0f, priest.GetNpcPosY() - 100.0f }, 30, 2, WHITE);
	}
}
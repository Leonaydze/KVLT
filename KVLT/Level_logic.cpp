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

extern Font font = LoadFont("");

void Init()
{
	font = LoadFont("Font.png");;
}

Font GetCurrentFont()
{
	return font;
}

bool PlayerOnGround(Player& player, Ground& ground) {
	player.SetPlayerCanJump(true);
	return (player.GetPlayerPositionX() + 88 >= ground.GetGroundPositionX() && player.GetPlayerPositionX() + 40 <= ground.GetGroundPositionX() + ground.GetGroundWidth()
		&& player.GetPlayerPositionY() + 128 >= ground.GetGroundPositionY() + 15 && player.GetPlayerPositionY() + 108 <= ground.GetGroundPositionY() + ground.GetGroundHeight());
}

void PlayerCantWalk(Player& player, Border& border) {
	if (player.GetPlayerPositionX() + 110 >= border.GetBorderPosX() && player.GetPlayerPositionX() + 110 <= border.GetBorderPosX() + 10
		&& player.GetPlayerPositionY() + 131 >= border.GetBorderPosY() + 1 && player.GetPlayerPositionY() <= border.GetBorderPosY() + border.GetBorderHeight() - 1) {
		player.SetPlayerCanWalk(-1);
		return;
	}
	if (player.GetPlayerPositionX() + 21 <= border.GetBorderPosX() + border.GetBorderWidth() && player.GetPlayerPositionX() + 21 >= border.GetBorderPosX() + border.GetBorderWidth() - 10
		&& player.GetPlayerPositionY() + 131 >= border.GetBorderPosY() + 1 && player.GetPlayerPositionY() <= border.GetBorderPosY() + border.GetBorderHeight() - 1) {
		player.SetPlayerCanWalk(1);
		return;
	}
	player.SetPlayerCanWalk(0);
}

void ResurrectionPlayer(Player& player, Altar& altar) {
	if (player.PlayerDeath()) {
		player.SetPlayerPositionV(altar.GetAltarPosV());
		player.SetPlayerHealth(player.GetMaxPlayerHealth() / 2);
	}
}

template<typename T>
bool PlayerCanTalkWithNpc(Player& player, T& other) {
	return (player.GetPlayerPositionX() + 88 >= other.GetNpcPosX() && player.GetPlayerPositionX() + 40 <= other.GetNpcPosX() + 128
		&& player.GetPlayerPositionY() + 20 >= other.GetNpcPosY() && player.GetPlayerPositionY() + 108 <= other.GetNpcPosY() + 128);
}
void UpgradePlayerLevel(Player& player, Priest& priest) {
	if (PlayerCanTalkWithNpc(player, priest) && !priest.NpcDeath()) {

	}
}

Camera2D _playerCamera;

Ground mainGroundFloor = Ground({ { -1000 , 1000 } , 5400, 1500, DARKGRAY });

//Border  = Border({ 500, 800 }, RAYWHITE, 40, 1000);
Ground _firstG = Ground({ 500, 900 }, 150, 30, RAYWHITE);
Ground _secondG = Ground({850, 800}, 150, 30, RAYWHITE);

void LEVEL_T_LOGIC(Player& player) {
	_playerCamera.target = { player.GetPlayerPositionX(), player.GetPlayerPositionY() - 200 };
	_playerCamera.offset = { 1920.0f / 2.0f, 1080.0f / 2.0f };
	_playerCamera.zoom = 1.0f;
	_playerCamera.rotation = 0.0f;

	player.PlayerController();

	if (player.IsPlayerJump() && !player.PlayerMaxJump() && player.GetPlayerCanJump()) {
		player.MoveVertically();
	}
	else if (PlayerOnGround(player, mainGroundFloor) || PlayerOnGround(player, _firstG) || PlayerOnGround(player, _secondG)) {
		player.SetPlayerCanJump(true);
		PlaySound(player._jump);
	}
	else if (player.PlayerMaxJump() || !player.IsPlayerJump()) {
		player.SetPlayerCanJump(false);
		player.MoveVerticallyDown();
	}
}

void LEVEL_T_DRAW(Player& player) {
	BeginMode2D(_playerCamera);
	DrawTextEx(font, "PRESS WASD TO MOVE", {-200, 700 }, 30, 3, RAYWHITE);
	DrawTextEx(font, " PRESS SPACE TO JUMP", {400, 700}, 30, 3, RAYWHITE);
	_firstG.GroundDraw();
	_secondG.GroundDraw();
	mainGroundFloor.GroundDraw();
	player.Draw();
}
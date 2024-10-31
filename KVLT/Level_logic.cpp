#include "Level_logic.h"

extern 	_gameScreen _currentScreen = mainMenu;

Camera2D _playerCamera;

_gameScreen GetCurrentGameScreen()
{
	return _currentScreen;
}

void SetCurrentScreen(_gameScreen curScreen)
{
	_currentScreen = curScreen;
}

bool PlayerOnGround(Player& player, Ground& ground) {
	player.SetPlayerCanJump(true);
	return (player.GetPlayerPositionX() + 88 >= ground.GetGroundPositionX() && player.GetPlayerPositionX() + 40 <= ground.GetGroundPositionX() + ground.GetGroundWidth()
		&& player.GetPlayerPositionY() + 128 >= ground.GetGroundPositionY() + 15 && player.GetPlayerPositionY() <= ground.GetGroundPositionY() + ground.GetGroundHeight());
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

Ground mainGroundFloor = Ground({ { -1000 , 1000 } , 5400, 1500, DARKGRAY });

Border lol = Border({ 500, 800 }, RAYWHITE, 40, 1000);
Ground lolG = Ground({ 500, 800 }, 20, 10, RAYWHITE);

void LEVEL_T_LOGIC(Player& player) {
	_playerCamera.target = { player.GetPlayerPositionX(), player.GetPlayerPositionY() - 200 };
	_playerCamera.offset = { 1920.0f / 2.0f, 1080.0f / 2.0f };
	_playerCamera.zoom = 1.0f;
	_playerCamera.rotation = 0.0f;

	player.PlayerController();

	if (player.IsPlayerJump() && !player.PlayerMaxJump() && player.GetPlayerCanJump()) {
		player.MoveVertically();
	}
	else if (PlayerOnGround(player, mainGroundFloor) || PlayerOnGround(player, lolG)) {
		player.SetPlayerCanJump(true);
	}
	else if (player.PlayerMaxJump() || !player.IsPlayerJump()) {
		player.MoveVerticallyDown();
	}
	PlayerCantWalk(player, lol);
}

void LEVEL_T_DRAW(Player& player) {
	BeginMode2D(_playerCamera);
	lol.Draw();
	lolG.GroundDraw();
	mainGroundFloor.GroundDraw();
	player.Draw();
}


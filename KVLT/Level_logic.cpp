#include "Level_logic.h"
#include "Player.h"
#include "Ground.h"
#include "Border.h"
#include "Altar.h"

extern 	_gameScreen _currentScreen = mainMenu;

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

Ground mainGroundFloor;
Border mainBorder;

void LEVEL_T_LOGIC(Player& player) {
	player.Init();

	player.PlayerController();
	player.Draw();

	if (player.IsPlayerJump() && !player.PlayerMaxJump() && player.GetPlayerCanJump()) {
		player.MoveVertically();
	}
	else if (PlayerOnGround(player, mainGroundFloor)) {
		player.SetPlayerCanJump(true);
	}
	else if (player.PlayerMaxJump() || !player.IsPlayerJump()) {
		player.MoveVerticallyDown();
	}
}

void LEVEL_T_DRAW(Player& player) {

}


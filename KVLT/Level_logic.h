#ifndef LEVEL_LOGIC_H
#define LEVEL_LOGIC_H
#include "Ground.h"
#include "Border.h"
#include "Altar.h"

bool TriggerEvent(float interval);

enum _gameScreen { mainMenu, LVL_TUTORIAL, LVL_1, LVL_2, LVL_3, LVL_4, UpgradeLevels };

_gameScreen GetCurrentGameScreen();

Vector2 GetLastPlayerPosition();
void SetLastPlayerPosition(Vector2 lastPlayerPosition);

void SetCurrentScreen(_gameScreen curScreen);

void Init();

Font GetCurrentFont();

void LEVEL_T_LOGIC(Player& player);
void LEVEL_T_DRAW(Player& player);

void ResurrectionPlayer(Player& player, Altar& altar);

#endif // !LEVEL_LOGIC_H
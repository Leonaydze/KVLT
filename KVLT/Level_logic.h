#ifndef LEVEL_LOGIC_H
#define LEVEL_LOGIC_H
#include "Player.h"
#include "Ground.h"
#include "Border.h"
#include "Altar.h"
#include "Clergy.h"

enum _gameScreen { mainMenu, LVL_TUTORIAL, LVL_1, LVL_2, LVL_3, LVL_4 };

_gameScreen GetCurrentGameScreen();

void SetCurrentScreen(_gameScreen curScreen);

void Init();

Font GetCurrentFont();

void LEVEL_T_LOGIC(Player& player);
void LEVEL_T_DRAW(Player& player);

void ResurrectionPlayer(Player& player, Altar& altar);


#endif // !LEVEL_LOGIC_H
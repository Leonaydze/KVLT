#ifndef LEVEL_LOGIC_H
#define LEVEL_LOGIC_H
#include "Ground.h"
#include "Border.h"
#include "Altar.h"
#include "Priest.h"
#include "PlayerWeapon.h"
#include "Boulder.h"
#include "Button.h"
#include "Thorn.h"

bool TriggerEvent(float interval);

enum _gameScreen { mainMenu, LVL_TUTORIAL, LVL_1, LVL_2, LVL_3, LVL_4, UpgradeLevels, Inventory, DEATH_SCREEN };

_gameScreen GetCurrentGameScreen();
void SetCurrentScreen(_gameScreen curScreen);

_gameScreen GetLastGameScreen();
void SetLastGameScreen(_gameScreen gameScreen);


Vector2 GetLastPlayerPosition();
void SetLastPlayerPosition(Vector2 lastPlayerPosition);

Font GetCurrentFont();

void Init();

void LEVEL_T_LOGIC(Player& player);
void LEVEL_T_DRAW(Player& player);

void DEATH_SCREEN_DRAW(Player& player);

bool WhereWasPlayer(Player& player);

#endif // !LEVEL_LOGIC_H
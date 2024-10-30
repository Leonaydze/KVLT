#ifndef LEVEL_LOGIC_H
#define LEVEL_LOGIC_H

enum _gameScreen { mainMenu, LVL_TUTORIAL, LVL_1, LVL_2, LVL_3, LVL_4 };

Player player;

_gameScreen GetCurrentGameScreen();

void SetCurrentScreen(_gameScreen curScreen);

#endif // !LEVEL_LOGIC_H
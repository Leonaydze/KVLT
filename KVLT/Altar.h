#ifndef ALTAR_H
#define ALTAR_H
#include "Player.h"

class Altar{
private:

	Vector2 _altarPosition = { 100, 700 };

	Texture2D _altarTexture = LoadTexture("");
	Rectangle _altarRectangle {0, 0, 102.4f, 102.4f};

	bool _playerWasAtAltar = false;
public:
	Altar();

	Altar(Vector2 altarPosition) : _altarPosition(altarPosition) {};

	void RegeneratePlayerHealth(Player &player);

	void Init();

	void Draw();

	Vector2 GetAltarPosV();

	bool GetPlayerWasAtAltar();
	void SetPlayerWasAtAltar(bool flag);

	float GetAltarPosX();
	float GetAltarPosY();
};

#endif // !ALTAR_H
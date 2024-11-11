#pragma once
#include <raylib.h>

class Flask {
private:
	int _maxHealCount = 35;

	Texture2D _flaskTexture = LoadTexture("");
public:
	int GetMaxHealCount();

	Texture2D GetTexture();

	void Init();
};


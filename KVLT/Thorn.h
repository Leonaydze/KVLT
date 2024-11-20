#ifndef THORN_H
#define THORN_H

#include <raylib.h>

class Thorn{
private:
	Vector2 _thornPos{};

	Texture2D _thornText = LoadTexture("");
	Rectangle _frameRec = {0.0f, 0.0f, 100.0f, 75.0f};

	short int _width = 100;
	short int _height = 75;

	float _thornSpeed = 0.0f;
public:
	enum _direction {DEFAULT, UP, DOWN};
	_direction _thornDirection = DEFAULT;


	Thorn();

	Thorn(Vector2 thornPos, Thorn::_direction thornDirection) : _thornPos(thornPos), _thornDirection(thornDirection) {}


	float GetThornPosX();
	float GetThornPosY();

	float GetThornWidth();
	float GetThornHeight();

	void Draw();
	void Init();

	void MoveVerticallyDown();

	void ThornSpeedNull();

	_direction GetThornDirection();

	float GetThornSpeed();
};

#endif // !THORN_H
#ifndef BOULDER_H
#define BOULDER_H

#include <raylib.h>
#include <iostream> 

class Boulder{
private:
	Vector2 _boulderStartPos = {};
	Vector2 _boulderPos = {};

	float _radius = 0;

	Color _boulderColor = {};

	float _boulderSpeed = 0.0f;
	float _boulderSpeedH = 0.0f;

	Texture2D _boulderText = LoadTexture("");
public:
	Boulder();

	Boulder(Vector2 boulderStartPos, float radius, Color boulderColor);

	void MoveVerticallyDown();

	void MoveHorizontally(int key, float distance);

	void Draw();

	float BoulderPosY();
	float BoulderPosX();

	float GetBoulderRadius();

	void BoulderSpeedNull();

	float GetBoulderSpeed();

	float GetBoulderSpeedH();

	void Init();
};

#endif // !BOULDER_H
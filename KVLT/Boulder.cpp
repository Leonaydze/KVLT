#include "Boulder.h"

Boulder::Boulder(){
}

Boulder::Boulder(Vector2 boulderStartPos, float radius, Color boulderColor)
{
	_boulderStartPos = boulderStartPos;
	_boulderPos = _boulderStartPos;

	_radius = radius;

	_boulderColor = boulderColor;
}

void Boulder::MoveVerticallyDown(){
	_boulderPos.y += _boulderSpeed;
	_boulderSpeed += 0.1f;
}

void Boulder::Draw()
{
	DrawCircle((int)_boulderPos.x, (int)_boulderPos.y, _radius, _boulderColor);
}

float Boulder::BoulderPosY()
{
	return _boulderPos.y;
}

float Boulder::BoulderPosX()
{
	return _boulderPos.x;
}

float Boulder::GetBoulderRadius()
{
	return _radius;
}

void Boulder::BoulderSpeedNull()
{
	_boulderSpeed = 0;
}

float Boulder::GetBoulderSpeed()
{
	return _boulderSpeed;
}

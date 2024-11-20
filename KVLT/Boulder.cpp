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

void Boulder::MoveHorizontally(int key, float distance){
	if (key == -1 && _boulderPos.x - _boulderStartPos.x >= -distance) {
		_boulderPos.x -= _boulderSpeedH;
		_boulderSpeedH += 0.1f;
		if (_boulderPos.x - _boulderStartPos.x <= -distance) {
			BoulderSpeedNull();
		}
		return;
	}
	if (key == 1 && _boulderPos.x - _boulderStartPos.x <= distance) {
		_boulderPos.x += _boulderSpeedH;
		_boulderSpeedH += 0.1f;
		if (_boulderPos.x - _boulderStartPos.x >= distance) {
			BoulderSpeedNull();
		}
		return;
	}
	if (key == 0) {
		std::cout << "Wrong Key For Boulder" << std::endl;
	}
}

void Boulder::Draw()
{
	DrawTexture(_boulderText, (int)_boulderPos.x, (int)_boulderPos.y, _boulderColor);
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
float Boulder::GetBoulderSpeedH()
{
	return _boulderSpeedH;
}

void Boulder::Init(){
	_boulderText = LoadTexture("Sprites\\Boulder.png");
	if (_radius < _boulderText.width) {
		_boulderText.width = (int)_radius;
		_boulderText.height = (int)_radius;
	}
	if (_radius > _boulderText.width) {
		_boulderText.width = (int)_radius;
		_boulderText.height = (int)_radius;
	}
}

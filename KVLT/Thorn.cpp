#include "Thorn.h"

Thorn::Thorn()
{
}

float Thorn::GetThornPosX(){
	return _thornPos.x;
}

float Thorn::GetThornPosY(){
	return _thornPos.y;
}

float Thorn::GetThornWidth(){
	return _width;
}

float Thorn::GetThornHeight() {
	return _height;
}

void Thorn::Draw(){
	DrawTextureRec(_thornText, _frameRec, { _thornPos.x, _thornPos.y }, WHITE);
}

void Thorn::Init(){
	_thornText = LoadTexture("Sprites\\Thorns.png");
	_thornText.width /= 2;
	_thornText.height /= 2;
	if (_thornDirection == DOWN) {
		_frameRec.height = -_frameRec.height;
	}

}

void Thorn::MoveVerticallyDown(){
	if (_thornDirection == DOWN) {
		_thornPos.y += _thornSpeed;
		_thornSpeed += 0.1f;
	}
}

void Thorn::ThornSpeedNull()
{
	_thornSpeed = 0.0f;
}

Thorn::_direction Thorn::GetThornDirection()
{
	return _thornDirection;
}

float Thorn::GetThornSpeed()
{
	return _thornSpeed;
}

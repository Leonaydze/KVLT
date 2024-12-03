#include "Border.h"

Border::Border(){
}

int Border::GetBorderPosX(){
	return static_cast<int>(_borderPosition.x);
}

int Border::GetBorderPosY(){
	return static_cast<int>(_borderPosition.y);
}

int Border::GetBorderWidth()
{
	return _borderWidth;
}

int Border::GetBorderHeight()
{
	return _borderHeight;
}

void Border::Draw()
{
	DrawRectangle(static_cast<int>(_borderPosition.x), static_cast<int>(_borderPosition.y), _borderWidth, _borderHeight, _borderColor);
}

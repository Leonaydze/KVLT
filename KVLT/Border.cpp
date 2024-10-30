#include "Border.h"

Border::Border(){
}

int Border::GetBorderPosX(){
	return (int)_borderPosition.x;
}

int Border::GetBorderPosY(){
	return (int)_borderPosition.y;
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
	DrawRectangle((int)_borderPosition.x, (int)_borderPosition.y, _borderWidth, _borderHeight, _borderColor);
}

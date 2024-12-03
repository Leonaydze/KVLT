#include "Button.h"

Button::_buttonAction Button::GetCurrentAction()
{
	return curAction;
}

bool Button::IsButtonEnabled()
{
	return _isEnabled;
}

void Button::EnableButton(bool isEnable)
{
	_isEnabled = isEnable;
}

void Button::Draw(){
	DrawRectangle(static_cast<int>(_buttonPos.x), static_cast<int>(_buttonPos.y), _width, _height, _buttonColor);
}

float Button::GetButtonPosX()
{
	return _buttonPos.x;
}

float Button::GetButtonPosY()
{
	return _buttonPos.y;
}

int Button::GetButtonWidth()
{
	return _width;
}

int Button::GetButtonHeight()
{
	return _height;
}

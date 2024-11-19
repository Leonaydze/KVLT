#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>

class Button{
private:
	Vector2 _buttonPos = {};

	Color _buttonColor = { 110, 110, 110, 255 };

	int _width = 50;
	int _height = 20;
	
	bool _isEnabled = false;
public:
	enum _buttonAction {DEFAULT ,MOVE, DROP};

	_buttonAction curAction = DEFAULT;

	Button() {}

	Button(Vector2 buttonPos, _buttonAction buttonAction) 
		: _buttonPos(buttonPos), curAction(buttonAction) {}

	_buttonAction GetCurrentAction();

	bool IsButtonEnabled();
	void EnableButton(bool isEnable);

	void Draw();

	float GetButtonPosX();
	float GetButtonPosY();

	int GetButtonWidth();
	int GetButtonHeight();
};

#endif // !BUTTON_H

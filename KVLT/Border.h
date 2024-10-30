#ifndef BORDER_H
#define BORDER_H
#include <raylib.h>

class Border {
private:
	int _borderWidth;
	int _borderHeight;
	Vector2 _borderPosition;
	Color _borderColor;
public:
	Border();

	Border(Vector2 borderPosition, Color borderColor, int borderWidth, int borderHeight) 
		: _borderPosition(borderPosition), _borderColor(borderColor), _borderWidth(borderWidth), _borderHeight(borderHeight) {}

	int GetBorderPosX();
	int GetBorderPosY();
	int GetBorderWidth();
	int GetBorderHeight();

	void Draw();
};

#endif // !BORDER_H
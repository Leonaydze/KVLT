#ifndef PRIEST_H
#define PRIEST_H
#include "NPC.h"

class Priest : public NPC{
private:
	Texture2D _npcTexture = LoadTexture("");
	Rectangle _frameRec{ 0, 0, 100, 100 };
public:
	Priest();

	Priest(Vector2 npcPosition) : NPC(npcPosition, 50, SKILL) {}

	inline void Init() override;

	~Priest();
};

#endif // !PRIEST_H
#ifndef PRIEST_H
#define PRIEST_H
#include "NPC.h"

class Priest : public NPC{
public:
	Priest();

	Priest(Vector2 npcPosition) : NPC(npcPosition, 50, SKILL) {}

	void Init() override;

	~Priest();
};

#endif // !PRIEST_H
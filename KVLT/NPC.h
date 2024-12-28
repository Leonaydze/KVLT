#ifndef NPC_H
#define NPC_H
#include <raylib.h>

class NPC {
protected:
	short int _npcHealth = 50;
	Vector2 _npcPosition = {};

	Texture2D _npcTexture = LoadTexture("");
	Rectangle _frameRec{ 0, 0, 100, 100 };
public:
	enum _Action {DEFAULT, SKILL, WEAPON};
	_Action _currentAction = DEFAULT;

	NPC();

	NPC(Vector2 npcPosition, short int npcHealth, _Action curAct) : _npcPosition(npcPosition), _npcHealth(npcHealth), _currentAction(curAct) {}

	inline short int GetNpcHealth();
	inline void ScaleNpcHealth(unsigned short int damage);

	inline float GetNpcPosX();
	inline float GetNpcPosY();

	inline bool NpcDeath();

	virtual inline void Init();
	void Draw();

	_Action GetAction();

	~NPC();
};


#endif // !NPC_H


#pragma once
#include "CGameObject.h"

class CQuestionBrick : public CGameObject
{
private:
	long bounceBegin = -1;
	float beginY;
public:
	CQuestionBrick();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void Bounce();
	void Render();
};
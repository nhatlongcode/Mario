#pragma once
#include "CGameObject.h"

class CCoin : public CGameObject
{
private:
public:
	CCoin();
	void SetState(int state);
	void Render();
};
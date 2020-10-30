#pragma once
#include "CMario.h"
class CBigMario : public CMario
{
public:
	CBigMario();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	
};


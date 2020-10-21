#pragma once
#include "CAnimationsManager.h"
class IAnimSetsManager 
{
public:
	virtual void Add(int id, LPANIM_SET ani) = 0;
	virtual LPANIM_SET Get(unsigned int id) = 0;
};

typedef IAnimSetsManager* LPANIMATIONSETS;
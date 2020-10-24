#pragma once
#include "CAnimationsManager.h"
class IAnimSetsManager 
{
public:
	virtual void Add(int id, LPANIMSET ani) = 0;
	virtual LPANIMSET Get(unsigned int id) = 0;
};

typedef IAnimSetsManager* LPANIMATIONSETS;
#pragma once
#include "IAnimSetsManager.h"

class CAnimationSetsManager : IAnimSetsManager
{
	virtual void Add(int id, LPANIM_SET ani);
	virtual LPANIM_SET Get(unsigned int id);
};
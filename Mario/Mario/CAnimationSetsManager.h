#pragma once
#include "IAnimSetsManager.h"

class CAnimationSetsManager : IAnimSetsManager
{
	unordered_map<int, LPANIM_SET> animation_sets;

	void Add(int id, LPANIM_SET ani);
	LPANIM_SET Get(unsigned int id);
};
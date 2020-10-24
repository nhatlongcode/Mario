#pragma once
#include "IAnimSetsManager.h"

class CAnimationSetsManager : public IAnimSetsManager
{
	unordered_map<int, LPANIMSET> animation_sets;

	void Add(int id, LPANIMSET ani);
	LPANIMSET Get(unsigned int id);
};
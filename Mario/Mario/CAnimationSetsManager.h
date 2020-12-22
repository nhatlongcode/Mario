#pragma once
#include "IAnimSetsManager.h"

class CAnimationSetsManager : public IAnimSetsManager
{
private:
	unordered_map<int, LPANIMSET> animation_sets;
public:
	void Add(int id, LPANIMSET ani) override;
	LPANIMSET Get(unsigned int id) override;
	void Clear() override;
};
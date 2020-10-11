#pragma once
#include "CAnimation.h"
#include <unordered_map>
class CAnimationsManager
{
private:
	std::unordered_map<int, LPANIMATION> animations;
public:
	void LoadResources();
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
};

#pragma once
#include "CAnimation.h"
#include "IAnimsManager.h"
#include <unordered_map>
class CAnimationsManager : public IAnimsManager
{
private:
	std::unordered_map<int, LPANIMATION> animations;
public:
	virtual void Add(int id, LPANIMATION ani);
	virtual LPANIMATION Get(int id);
	virtual void Clear();
};


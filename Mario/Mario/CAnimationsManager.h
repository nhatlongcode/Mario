#pragma once
#include "CAnimation.h"
#include "IAnimsManager.h"
#include <unordered_map>
class CAnimationsManager : public IAnimsManager
{
private:
	std::unordered_map<int, LPANIMATION> animations;
public:
	void Add(int id, LPANIMATION ani) override;
	LPANIMATION Get(int id) override;
	void Clear() override;
};


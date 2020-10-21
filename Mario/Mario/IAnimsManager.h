#pragma once
#include "CAnimation.h"
 class IAnimsManager
{
public:
	 virtual void Add(int id, LPANIMATION ani) = 0;
	 virtual LPANIMATION Get(int id) = 0;
	 virtual void Clear() = 0;
};

 typedef IAnimsManager* LPANIMATIONS;
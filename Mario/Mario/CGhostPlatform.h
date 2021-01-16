#pragma once
#include "CGameObject.h"


class CGhostPlatform : public CGameObject
{
public:
	CGhostPlatform();
	virtual bool GetThrought(ObjectTag tag, float nx, float ny) override;
	void Render();
};
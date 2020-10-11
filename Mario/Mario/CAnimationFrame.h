#pragma once
#include "CSprite.h"
class CAnimationFrame
{
private:
	LPSPRITE sprite;
	DWORD time;
public:
	CAnimationFrame(LPSPRITE sprite, int time);
	DWORD GetTime();
	LPSPRITE GetSprite();
};
typedef CAnimationFrame* LPFRAME;



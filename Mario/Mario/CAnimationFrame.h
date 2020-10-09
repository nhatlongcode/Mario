#ifndef CANIMATIONFRAME_H
#define CANIMATIONFRAME_H

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
#endif


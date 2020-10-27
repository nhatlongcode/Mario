#include "CAnimationFrame.h"

CAnimationFrame::CAnimationFrame(LPSPRITE sprite, int time)
{
	this->sprite = sprite;
	this->time = time;
}

DWORD CAnimationFrame::GetTime()
{
	return time;
}

LPSPRITE CAnimationFrame::GetSprite()
{
	return sprite;
}

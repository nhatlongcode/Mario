#pragma once
#include "CChar.h"

class CFontInfo
{
private:
	int ascii, top, left, width, height, texID;
public:
	CFontInfo();
	CFontInfo(int ascii, int top, int left, int width, int height, int texID);
	CChar* GetChar(float scaleX, float scaleY);
};
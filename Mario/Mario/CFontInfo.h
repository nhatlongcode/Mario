#pragma once
#include "CFont.h"

class CFontInfo
{
private:
	int ascii, top, left, width, height, texID;
public:
	CFontInfo(int ascii, int top, int left, int width, int height, int texID);
	CFont* GetFont();
};
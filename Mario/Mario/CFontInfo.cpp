#include "CFontInfo.h"
#include "CLocator.h"
#include "ITexsManager.h"

CFontInfo::CFontInfo()
{
	ascii = 0;
	top = 0;
	left = 0;
	width = 0;
	height = 0;
	texID = 0;
}

CFontInfo::CFontInfo(int ascii, int top, int left, int width, int height, int texID)
{
	this->ascii = ascii;
	this->top = top;
	this->left = left;
	this->width = width;
	this->height = height;
	this->texID = texID;
}

CChar* CFontInfo::GetChar(float scaleX, float scaleY)
{
	auto tex = CLocator<ITexsManager>().Get()->Get(texID);
	return new CChar(left, top, width, height, scaleX, scaleY, tex);
}


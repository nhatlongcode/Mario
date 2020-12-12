#include "CFontInfo.h"

CFontInfo::CFontInfo(int ascii, int top, int left, int width, int height, int texID)
{
	this->ascii = ascii;
	this->top = top;
	this->left = left;
	this->width = width;
	this->height = height;
	this->texID = texID;
}

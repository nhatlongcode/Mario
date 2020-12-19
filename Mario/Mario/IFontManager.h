#pragma once
#include <unordered_map>
#include "CFontInfo.h"

class IFontManager
{
public:
	virtual CFontInfo* GetFont(int fontID, int asciiID) = 0;
	virtual void AddFont(int fontID, int asciiID, int top, int left, int width, int height) = 0;
};
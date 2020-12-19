#pragma once
#include "IFontManager.h"

class CFontManager : public IFontManager
{
private:
	std::unordered_map<int, std::unordered_map<int, CFontInfo>> fonts;
	
	virtual CFontInfo GetFont(int fontID, int asciiID) override;
};
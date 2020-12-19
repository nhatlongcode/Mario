#pragma once
#include "IFontManager.h"

class CFontManager : public IFontManager
{
private:
	std::unordered_map<int, std::unordered_map<int, CFontInfo*>> fonts;
	CFontInfo* GetFont(int fontID, int asciiID) override;
	void AddFont(int fontID, int asciiID, int top, int left, int width, int height) override;
public:
	CFontManager();
};
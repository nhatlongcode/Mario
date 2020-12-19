#include "CFontManager.h"


CFontInfo* CFontManager::GetFont(int fontID, int asciiID)
{
    return fonts[fontID][asciiID];
}

void CFontManager::AddFont(int fontID, int asciiID, int top, int left, int width, int height)
{
    CFontInfo* font = new CFontInfo(asciiID, top, left, width, height, fontID); // texID = fontID
    fonts[fontID][asciiID] = font;

}

CFontManager::CFontManager()
{
    fonts.clear();
}

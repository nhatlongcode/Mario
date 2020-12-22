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

void CFontManager::Clear()
{
    for (auto x : fonts)
    {
        for (auto y : x.second)
        {
            auto element = y.second;
            if (element != nullptr) delete element;
        }
    }
    fonts.clear();
}

CFontManager::CFontManager()
{
    fonts.clear();
}

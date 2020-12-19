#include "CFontManager.h"


CFontInfo CFontManager::GetFont(int fontID, int asciiID)
{
    return fonts[fontID][asciiID];
}

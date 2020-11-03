#include "CTileMap.h"
#include "CLocator.h"
#include "ISpritesManager.h"

CTileMap::CTileMap(int x, int y, int spriteID)
{
	this->x = x;
	this->y = y;
	this->spriteID = spriteID;
}

void CTileMap::Render()
{
	//DebugOut(L"spriteID: %d\n", spriteID);
	CLocator<ISpritesManager>().Get()->Get(spriteID)->Draw(x, y);
}

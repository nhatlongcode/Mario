#include "CSpritesManager.h"
#include "Utils.h"


void CSpritesManager::Add(int id, int left, int top, int width, int height, float scaleX, float scaleY, int xPivot, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE sprite = new CSprite(id, left, top, width, height, scaleX, scaleY, xPivot, tex);
	sprites[id] = sprite;
	DebugOut(L"SPRITES ID: %d ADDED \n", id);
}

LPSPRITE CSpritesManager::Get(int id)
{
	return sprites[id];
}

void CSpritesManager::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}

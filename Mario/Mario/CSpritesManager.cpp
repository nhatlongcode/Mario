#include "CSpritesManager.h"



void CSpritesManager::Add(int id, int left, int top, int width, int height, int scaleX, int scaleY, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE sprite = new CSprite(id, left, top, width, height, scaleX, scaleY, tex);
	sprites[id] = sprite;
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

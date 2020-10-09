#include "CSpritesManager.h"

void CSpritesManager::Init()
{
}

void CSpritesManager::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE sprite = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = sprite;
}

LPSPRITE CSpritesManager::Get(int id)
{
	return sprites[id];
}

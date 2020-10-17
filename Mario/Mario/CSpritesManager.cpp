#include "CSpritesManager.h"



void CSpritesManager::Add(int id, int left, int top, int width, int height,Vector2 scale, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE sprite = new CSprite(id, left, top, width, height, scale, tex);
	sprites[id] = sprite;
}

LPSPRITE CSpritesManager::Get(int id)
{
	return sprites[id];
}

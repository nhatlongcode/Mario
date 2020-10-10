#include "CSpritesManager.h"

void CSpritesManager::Init()
{
	LPTEXTURE texMario = CLocator<CTexturesManager>().Get()->Get(ID_TEX_MARIO);
	Add(10001, 246, 154, 259, 181, texMario);
	Add(10002, 275, 154, 290, 181, texMario);
	Add(10003, 304, 154, 321, 181, texMario);

	Add(10011, 186, 154, 199, 181, texMario);
	Add(10012, 155, 154, 170, 181, texMario);
	Add(10013, 125, 154, 140, 181, texMario);
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

#pragma once
#include "CSprite.h"
#include "CTexturesManager.h"
#include "MarioDefines.h"
#include <d3dx9.h>
#include <unordered_map>

class CSpritesManager
{
private:
	std::unordered_map<int, LPSPRITE> sprites;
public:
	void Add(int id, int left, int top, int width, int height, Vector2 scale, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
};
typedef CSpritesManager* LPSPRITES;
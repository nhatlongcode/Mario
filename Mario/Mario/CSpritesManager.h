#pragma once
#include "CSprite.h"
#include "CTexturesManager.h"
#include "ISpritesManager.h"
#include "MarioDefines.h"
#include <d3dx9.h>
#include <unordered_map>

class CSpritesManager : public ISpritesManager
{
private:
	std::unordered_map<int, LPSPRITE> sprites;
public:
	void Add(int id, int left, int top, int width, int height, int scaleX, int scaleY, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
	void Clear();
};

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
	void Add(int id, int left, int top, int width, int height, float scaleX, float scaleY, int xPivot, LPDIRECT3DTEXTURE9 tex) override;
	LPSPRITE Get(int id) override;
	void Clear() override;
};

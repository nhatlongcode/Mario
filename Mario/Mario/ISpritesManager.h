#pragma once
#include "CSprite.h"
class ISpritesManager
{
public:
	virtual void Add(int id, int left, int top, int width, int height, int scaleX, int scaleY, int xPivot, LPDIRECT3DTEXTURE9 tex) = 0;
	virtual LPSPRITE Get(int id) = 0;
	virtual void Clear() = 0;
};

typedef ISpritesManager* LPSPRITES;
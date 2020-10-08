#ifndef CSPRITE_H
#define CSPRITE_H

#include <d3dx9.h>
#include <unordered_map>
#include "CLocator.h"
#include "CDirectX.h"

class CSprite
{
private:
	int id;
	int left;
	int top;
	int bottom;
	int right;
	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, int alpha = 255);
};
typedef CSprite* LPSPRITE;
#endif


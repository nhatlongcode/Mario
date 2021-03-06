#pragma once
#include <d3dx9.h>
#include <unordered_map>
#include "MarioDefines.h"
#include "Utils.h"
#include "CLocator.h"
#include "CDirectX.h"

class CSprite
{
private:
	int id;
	int left;
	int top;
	int width;
	int height;
	float scaleX;
	float scaleY;
	int xPivot;
	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int width, int height, float scaleX, float scaleY, int xPivot,  LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, int direction = DIRECTION_RIGHT, int alpha = 255);
};
typedef CSprite* LPSPRITE;


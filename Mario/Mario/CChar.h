#pragma once
#include <d3dx9.h>
#include <unordered_map>
#include "CLocator.h"
#include "CDirectX.h"

class CChar
{
private:
	int id, left, top, width, height, size;
	LPDIRECT3DTEXTURE9 texture;
	float x, y;
public:
	CChar(int id, int left, int top, int width, int height, int size, LPDIRECT3DTEXTURE9 texture);
	void Render();
	void SetSize(int size);
	void SetPosition(float x, float y);
		
};

typedef CChar* LPCHAR;
#pragma once
#include <d3dx9.h>
#include "MarioDefines.h"
class CDirectX
{
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DSURFACE9 backBuffer;
	LPD3DXSPRITE spriteHandler;
	LPDIRECT3DTEXTURE9 texBrick;
public:
	void InitDirectX(HWND hWnd);
	void Render();
};


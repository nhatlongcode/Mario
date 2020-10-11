#pragma once
#include <d3dx9.h>
#include "MarioDefines.h"
#include "CSprite.h"
#include "CTexturesManager.h"

class CDirectX
{
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DSURFACE9 backBuffer;
	LPD3DXSPRITE spriteHandler;
	HWND hWnd;
	void InitDirectX();
public:
	CDirectX(HWND hwnd);
	void Init();
	LPDIRECT3DDEVICE9 Device();
	LPDIRECT3DSURFACE9 BackBuffer();
	LPD3DXSPRITE SpriteHandler();
};


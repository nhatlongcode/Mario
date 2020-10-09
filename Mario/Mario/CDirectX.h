#ifndef CDIRECTX_H
#define CDIRECTX_H

#include <d3dx9.h>
#include "MarioDefines.h"
#include "CAbstractService.h"
#include "CSprite.h"
#include "CTexturesManager.h"

class CDirectX : public CAbstractService
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
	void Render();
	LPDIRECT3DDEVICE9 Device();
	LPD3DXSPRITE SpriteHandler();
};
#endif


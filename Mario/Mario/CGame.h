#pragma once
#include <d3dx9.h>
#include "MarioDefines.h"
#include "CWindow.h"
#include "CDirectX.h"
#include "CLocator.h"
#include "CGameObject.h"
#include "CTexturesManager.h"
#include "CAnimationsManager.h"

class CGame
{
private:
	CWindow* wnd;
	CDirectX* directx;
	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DSURFACE9 backBuffer;
	LPD3DXSPRITE spriteHandler;
	void Update(DWORD dt);
	void Render();
	CGameObject* mario;
public:
	CGame();
	~CGame();
	void InitGame();
	int Run();

};


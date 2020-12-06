#include "CDirectX.h"
#include "CGame.h"


CDirectX::CDirectX(HWND hwnd)
{
	hWnd = hwnd;
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	backBuffer = NULL;
	d3ddv = NULL;
	spriteHandler = NULL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	CGame::Instance()->SetWidthHeight(r.right + 1, r.bottom + 1);

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"[INFO] InitGame is done\n");
}



LPDIRECT3DDEVICE9 CDirectX::Device()
{
	return d3ddv;
}

LPDIRECT3DSURFACE9 CDirectX::BackBuffer()
{
	return backBuffer;
}

LPD3DXSPRITE CDirectX::SpriteHandler()
{
	return spriteHandler;
}

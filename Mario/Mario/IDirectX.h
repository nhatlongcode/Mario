#pragma once
#include <d3dx9.h>
class IDirectX
{
public:
	virtual LPDIRECT3DDEVICE9 Device() = 0;
	virtual LPDIRECT3DSURFACE9 BackBuffer() = 0;
	virtual LPD3DXSPRITE SpriteHandler() = 0;
};
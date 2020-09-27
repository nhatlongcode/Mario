#pragma once
#include "CWindow.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "MarioDefines.h"

class CGame
{
private:
	static CGame* _instance;
	CWindow wnd;
	LPD3DXSPRITE spriteHandler;
	LPDIRECT3DTEXTURE9 texBrick;

	void Update(DWORD dt);
	void Render();
public:
	~CGame();
	static CGame* Instance();
	void PublicTestVoid();
	void InitGame(HINSTANCE hInstance, int nCmdShow);
	void InitDirectX();
	int Run();

};


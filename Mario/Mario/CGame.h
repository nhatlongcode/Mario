#pragma once
#include "CWindow.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "MarioDefines.h"
#include "CDirectX.h"

class CGame
{
private:
	static CGame* _instance;
	CWindow wnd;
	CDirectX directx;

	void Update(DWORD dt);
public:
	~CGame();
	static CGame* Instance();
	void InitGame(HINSTANCE hInstance, int nCmdShow);
	int Run();

};


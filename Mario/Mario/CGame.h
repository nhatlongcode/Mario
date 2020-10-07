#ifndef CGAME_H
#define CGAME_H
#endif

#include "CWindow.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "MarioDefines.h"
#include "CDirectX.h"

class CGame
{
private:
	CWindow wnd;
	CDirectX directx;

	void Update(DWORD dt);
public:
	~CGame();
	void InitGame(HINSTANCE hInstance, int nCmdShow);
	int Run();

};


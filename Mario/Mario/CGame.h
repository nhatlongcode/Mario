#ifndef CGAME_H
#define CGAME_H

#include "CWindow.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "MarioDefines.h"
#include "CDirectX.h"
#include "CLocator.h"

class CGame
{
private:
	CWindow* wnd;
	CDirectX* directx;
	void Update(DWORD dt);
public:
	CGame();
	~CGame();
	void InitGame();
	int Run();

};
#endif


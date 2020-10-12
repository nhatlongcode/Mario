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
	void Update(DWORD dt);
	void Render();
	void LoadResources();
	CGameObject* mario;
public:
	CGame();
	~CGame();
	void InitGame();
	int Run();

};


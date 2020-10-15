#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "CGame.h"
#include "CLocator.h"
#include "CTexturesManager.h"
#include "CAnimationsManager.h"
#include "CSpritesManager.h"
#include "MarioDefines.h"
#include "CSprite.h"


void InitLocator(HINSTANCE hInstance, int nCmdShow)
{
	CWindow* window = new CWindow(hInstance, nCmdShow);

	CDirectX* directx = new CDirectX(window->GetHandleWindow());
	CTexturesManager* textures = new CTexturesManager();
	CSpritesManager* sprites = new CSpritesManager();
	CAnimationsManager* animations = new CAnimationsManager();

	CLocator<CWindow>().Add(window);
	CLocator<CDirectX>().Add(directx);
	CLocator<CTexturesManager>().Add(textures); 
	CLocator<CSpritesManager>().Add(sprites);
	CLocator<CAnimationsManager>().Add(animations);


}

void Clear()
{
	delete CLocator<CWindow>().Get();
	delete CLocator<CDirectX>().Get();
	delete CLocator<CTexturesManager>().Get();
	delete CLocator<CSpritesManager>().Get();
	delete CLocator<CAnimationsManager>().Get();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//CGame* MarioGame = CGame::Instance();
	//MarioGame->InitGame(hInstance, nCmdShow);


	InitLocator(hInstance, nCmdShow);

	CGame* Mario = new CGame();
	Mario->InitGame();
	Mario->Run();

	Clear();
	//locator->Get<CTexturesManager>()->Init();
	return 0;
}


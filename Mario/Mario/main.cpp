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
	IWindow* window = new CWindow(hInstance, nCmdShow);

	IDirectX* directx = new CDirectX(window->GetHandleWindow());
	ITexsManager* textures = new CTexturesManager();
	ISpritesManager* sprites = new CSpritesManager();
	IAnimsManager* animations = new CAnimationsManager();

	CLocator<IWindow>().Add(window);
	CLocator<IDirectX>().Add(directx);
	CLocator<ITexsManager>().Add(textures); 
	CLocator<ISpritesManager>().Add(sprites);
	CLocator<IAnimsManager>().Add(animations);


}

void Clear()
{
	delete CLocator<IWindow>().Get();
	delete CLocator<IDirectX>().Get();
	delete CLocator<ITexsManager>().Get();
	delete CLocator<ISpritesManager>().Get();
	delete CLocator<IAnimsManager>().Get();
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


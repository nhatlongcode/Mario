#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "CGame.h"
#include "CLocator.h"
#include "CTexturesManager.h"
#include "CAnimationsManager.h"
#include "MarioDefines.h"
#include "CSprite.h"

void InitLocator(HINSTANCE hInstance, int nCmdShow)
{
	CWindow* window = new CWindow(hInstance, nCmdShow);

	CDirectX* directx = new CDirectX(window->GetHandleWindow());
	CTexturesManager* textures = new CTexturesManager();
	CAnimationsManager* animations = new CAnimationsManager();

	CLocator<CWindow>().Add(window);
	CLocator<CDirectX>().Add(directx);
	CLocator<CTexturesManager>().Add(textures); textures->LoadResources();
	CLocator<CAnimationsManager>().Add(animations);

}

void Clear()
{

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//CGame* MarioGame = CGame::Instance();
	//MarioGame->InitGame(hInstance, nCmdShow);


	InitLocator(hInstance, nCmdShow);

	CGame* Mario = new CGame();
	Mario->InitGame();
	Mario->Run();


	//locator->Get<CTexturesManager>()->Init();
	return 0;
}


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
	window->Init();
	CLocator<CWindow>().Add(window);

	CDirectX* directx = new CDirectX(CLocator<CWindow>().Get()->GetHandleWindow());
	CTexturesManager* textures = new CTexturesManager();
	CAnimationsManager* animations = new CAnimationsManager();

	CLocator<CDirectX>().Add(directx); directx->Init();
	CLocator<CTexturesManager>().Add(textures); textures->Init();
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


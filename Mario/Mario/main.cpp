#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "CGame.h"
#include "CLocator.h"
#include "CTexturesManager.h"
#include "MarioDefines.h"
#include "CSprite.h"

void InitLocator(HINSTANCE hInstance, int nCmdShow)
{
	CLocator* locator = CLocator::Instance();
	LPService window = new CWindow(hInstance, nCmdShow);
	window->Init();
	locator->Add(window);

	LPService directx = new CDirectX(locator->Get<CWindow>()->GetHandleWindow());
	LPService textures = new CTexturesManager();

	locator->Add(directx); directx->Init();
	locator->Add(textures); textures->Init();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//CGame* MarioGame = CGame::Instance();
	//MarioGame->InitGame(hInstance, nCmdShow);


	InitLocator(hInstance, nCmdShow);

	CGame* Mario = new CGame();

	Mario->Run();


	//locator->Get<CTexturesManager>()->Init();
	return 0;
}


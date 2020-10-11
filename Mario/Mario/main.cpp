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
	
	CLocator<CDirectX>().Add(directx);
	CLocator<CTexturesManager>().Add(textures); 
	CLocator<CSpritesManager>().Add(sprites);
	CLocator<CAnimationsManager>().Add(animations);

	textures->LoadResources();
	sprites->LoadResources();
	animations->LoadResources();

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


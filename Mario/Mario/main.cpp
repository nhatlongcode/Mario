#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "CGame.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//CGame* MarioGame = CGame::Instance();
	//MarioGame->InitGame(hInstance, nCmdShow);
	CGame* game = CGame::Instance();
	game->InitGame(hInstance, nCmdShow);
	game->Run();
	return 0;
}
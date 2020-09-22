#include "CGame.h"

CGame::~CGame()
{
}

CGame* CGame::Instance()
{
	if (_instance == NULL)
	{
		_instance = new CGame();
	}
	return _instance;
}

void CGame::PublicTestVoid()
{
	
}

void CGame::InitGame(HINSTANCE hInstance, int nCmdShow)
{
	//wnd = new CWindow();
	wnd.CreateGameWindow(hInstance, nCmdShow);
}


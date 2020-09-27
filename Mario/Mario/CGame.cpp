#include "CGame.h"

CGame* CGame::_instance = NULL;


void CGame::Update(DWORD dt)
{

}

void CGame::Render()
{
	if (d3ddv->BeginScene())
	{
		// Clear screen (back buffer) with a color
		d3ddv->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXVECTOR3 p(1.0f, 100.0f, 0);

		//D3DXVECTOR3 p(100.0f,10.0f, 0);
		spriteHandler->Draw(texBrick, NULL, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));

		spriteHandler->End();
		d3ddv->EndScene();
	}
}

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

void CGame::InitDirectX()
{

}



int CGame::Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / 60;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;

}


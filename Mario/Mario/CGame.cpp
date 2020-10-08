#include "CGame.h"


void CGame::Update(DWORD dt)
{

}


CGame::CGame()
{
	wnd = CLocator::Instance()->Get<CWindow>();
	directx = CLocator::Instance()->Get<CDirectX>();
}

CGame::~CGame()
{

}



void CGame::InitGame()
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
			directx->Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;

}


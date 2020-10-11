#include "CGame.h"


void CGame::Update(DWORD dt)
{
	mario->Update(dt);
}

void CGame::Render()
{
	if (d3ddv->BeginScene())
	{
		// Clear screen (back buffer) with a color
		d3ddv->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);


		CSprite* sprite = new CSprite(1, 246, 154, 260, 181, CLocator<CTexturesManager>().Get()->Get(ID_TEX_MARIO));
		sprite->Draw(0, 0);
		mario->Render();
		spriteHandler->End();
		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}


CGame::CGame()
{
	//wnd = CLocator::Instance()->Get<CWindow>();
	//directx = CLocator::Instance()->Get<CDirectX>();
	wnd = CLocator<CWindow>().Get();
	directx = CLocator<CDirectX>().Get();
	mario = new CGameObject();
	mario->SetPosition(10.0f, 100.0f);
	LPANIMATION ani = CLocator<CAnimationsManager>().Get()->Get(500);
	mario->ani = ani;
}

CGame::~CGame()
{

}



void CGame::InitGame()
{
	backBuffer = CLocator<CDirectX>().Get()->BackBuffer();
	d3ddv = CLocator<CDirectX>().Get()->Device();
	spriteHandler = CLocator<CDirectX>().Get()->SpriteHandler();
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


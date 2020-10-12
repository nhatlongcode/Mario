#include "CGame.h"


void CGame::Update(DWORD dt)
{
	mario->Update(dt);
}

void CGame::Render()
{
	LPDIRECT3DSURFACE9 backBuffer = CLocator<CDirectX>().Get()->BackBuffer();
	LPDIRECT3DDEVICE9 d3ddv = CLocator<CDirectX>().Get()->Device();
	LPD3DXSPRITE spriteHandler = CLocator<CDirectX>().Get()->SpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear screen (back buffer) with a color
		d3ddv->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		mario->Render();
		spriteHandler->End();
		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void CGame::LoadResources()
{
	LPTEXTURES texs = CLocator<CTexturesManager>().Get();
	LPSPRITES sprites = CLocator<CSpritesManager>().Get();
	LPANIMATIONS anis = CLocator<CAnimationsManager>().Get();

	texs->Add("TEX_MARIO", PATH_TEX_MARIO, D3DCOLOR_XRGB(255, 255, 255));
	auto texMario = texs->Get("TEX_MARIO");

	sprites->Add(10001, 246, 154, 259, 181, texMario);
	sprites->Add(10002, 275, 154, 290, 181, texMario);
	sprites->Add(10003, 304, 154, 321, 181, texMario);

	sprites->Add(10011, 186, 154, 199, 181, texMario);
	sprites->Add(10012, 155, 154, 170, 181, texMario);
	sprites->Add(10013, 125, 154, 140, 181, texMario);

	LPANIMATION ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	anis->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	anis->Add(501, ani);

}


CGame::CGame()
{

}

CGame::~CGame()
{

}



void CGame::InitGame()
{
	LoadResources();
	mario = new CGameObject();
	mario->SetPosition(10.0f, 100.0f);
	LPANIMATION ani = CLocator<CAnimationsManager>().Get()->Get(500);
	mario->ani = ani;
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


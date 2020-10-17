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
	LPANIMATIONS anims = CLocator<CAnimationsManager>().Get();
	Vector2 right(1,1);
	Vector2 left(-1, 1);


	texs->Add("TEX_MARIO", PATH_TEX_MARIO, D3DCOLOR_XRGB(255, 255, 255));
	auto texMario = texs->Get("TEX_MARIO");
	LPANIMATION anim;
	// BIG MARIO
	// IDLE		
	sprites->Add(10022, 197, 48, 14, 27, right, texMario);

	anim = new CAnimation();
	anim->Add(10022);
	anims->Add(MARIO_ANI_IDLE_RIGHT, anim);

	sprites->Add(11022, 197, 48, 14, 27, left, texMario);

	anim = new CAnimation();
	anim->Add(11022);
	anims->Add(MARIO_ANI_IDLE_LEFT, anim);
	// WALK
	sprites->Add(10023, 197, 48, 14, 27, right, texMario);
	sprites->Add(10024, 214, 48, 16, 27, right, texMario);
	sprites->Add(10025, 233, 49, 16, 26, right, texMario);

	anim = new CAnimation();
	anim->Add(10023);
	anim->Add(10024);
	anim->Add(10025);
	anims->Add(MARIO_ANI_WALKING_RIGHT, anim);

	sprites->Add(11023, 197, 48, 14, 27, left, texMario);
	sprites->Add(11024, 214, 48, 16, 27, left, texMario);
	sprites->Add(11025, 233, 49, 16, 26, left, texMario);

	anim = new CAnimation();
	anim->Add(11023);
	anim->Add(11024);
	anim->Add(11025);
	anims->Add(MARIO_ANI_WALKING_LEFT, anim);

	mario->AddAnimation(MARIO_ANI_IDLE_RIGHT);
	mario->AddAnimation(MARIO_ANI_IDLE_LEFT);
	mario->AddAnimation(MARIO_ANI_WALKING_RIGHT);
	mario->AddAnimation(MARIO_ANI_WALKING_LEFT);


}


CGame::CGame()
{

}

CGame::~CGame()
{

}



void CGame::InitGame()
{
	mario = new CMario();
	mario->SetPosition(10.0f, 100.0f);
	LoadResources();
	input = new CInput(CLocator<CWindow>().Get()->GetHandleWindow(), mario);
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
			input->ProcessKeyboard();
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;

}


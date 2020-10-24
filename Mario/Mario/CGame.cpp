#include "CGame.h" 
#include "CScenePlay.h"
#include "CLocator.h"
#include "CAnimationsManager.h"
#include <iostream>
#include <fstream>
CGame* CGame::instance = NULL;

void CGame::Update(DWORD dt)
{
	mario->Update(dt);
}

void CGame::Render()
{
	LPDIRECT3DSURFACE9 backBuffer = CLocator<IDirectX>().Get()->BackBuffer();
	LPDIRECT3DDEVICE9 d3ddv = CLocator<IDirectX>().Get()->Device();
	LPD3DXSPRITE spriteHandler = CLocator<IDirectX>().Get()->SpriteHandler();

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
	LPTEXTURES texs = CLocator<ITexsManager>().Get();
	LPSPRITES sprites = CLocator<ISpritesManager>().Get();
	LPANIMATIONS anims = CLocator<IAnimsManager>().Get();
	Vector2 right(1,1);
	Vector2 left(-1, 1);

	/*
	texs->Add(TEX_MARIO_ID, TEX_MARIO_PATH, D3DCOLOR_XRGB(255, 255, 255));
	auto texMario = texs->Get(TEX_MARIO_ID);
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

	*/
}

void CGame::Load(LPCWSTR filePath)
{
	DebugOut(L"[INFO] Start loading game file : %s\n", filePath);

	ifstream f;
	f.open(filePath);
	char str[MAX_GAME_LINE];

	// current resource section flag
	int section = GAME_FILE_SECTION_UNKNOWN;

	while (f.getline(str, MAX_GAME_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") { section = GAME_FILE_SECTION_SETTINGS; continue; }
		if (line == "[SCENES]") { section = GAME_FILE_SECTION_SCENES; continue; }

		//
		// data section
		//
		switch (section)
		{
		case GAME_FILE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case GAME_FILE_SECTION_SCENES: _ParseSection_SCENES(line); break;
		}
	}
	f.close();

	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", filePath);

	SwitchScene(current_scene);
}

void CGame::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start")
		current_scene = atoi(tokens[1].c_str());
	else
		DebugOut(L"[ERROR] Unknown game setting %s\n", ToWSTR(tokens[0]).c_str());
}

void CGame::_ParseSection_SCENES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	int id = atoi(tokens[0].c_str());
	LPCWSTR path = ToLPCWSTR(tokens[1]);

	LPSCENE scene = new CScenePlay(id, path);
	scenes[id] = scene;
}

void CGame::SwitchScene(int scene_id)
{
	DebugOut(L"[INFO] Switching to scene %d\n", scene_id);

	scenes[current_scene]->Unload();;

	CLocator<ITexsManager>().Get()->Clear();
	CLocator<ISpritesManager>().Get()->Clear();
	CLocator<IAnimsManager>().Get()->Clear();

	current_scene = scene_id;
	LPSCENE s = scenes[scene_id];
	SetKeyHandler(s->GetKeyEventHandler());
	s->Load();
}


CGame* CGame::Instance()
{
	if (instance == NULL)
	{
		instance = new CGame();
	}
	return instance;
}

CGame::~CGame()
{

}



void CGame::InitGame()
{
	mario = new CMario(100,100);
	mario->SetPosition(10.0f, 100.0f);
	Load(L"mario-sample.txt");
	input = new CInput(CLocator<IWindow>().Get()->GetHandleWindow(),keyHandler);
	//LoadResources();
}


int CGame::Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;
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

void CGame::SetKeyHandler(LPKEYEVENTHANDLER keyHandler)
{
	this->keyHandler = keyHandler;
}

bool CGame::IsKeyDown(int keyCode)
{
	return input->IsKeyDown(keyCode);
}


#include "CGame.h" 
#include "CScenePlay.h"
#include "CLocator.h"
#include "CAnimationsManager.h"
#include "CInput.h"
#include <iostream>
#include <fstream>
CGame* CGame::instance = NULL;

void CGame::Update(DWORD dt)
{
	//mario->Update(dt);
	scenes[currentSceneID]->Update(dt);
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

		//mario->Render();
		scenes[currentSceneID]->Render();
		//CLocator<ISpritesManager>().Get()->Get(10023)->Draw(300.0f, 300.0f); // test sprite
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

	SwitchScene(currentSceneID);
}

void CGame::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start")
		currentSceneID = atoi(tokens[1].c_str());
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

	scenes[currentSceneID]->Unload();;

	CLocator<ITexsManager>().Get()->Clear();
	CLocator<ISpritesManager>().Get()->Clear();
	CLocator<IAnimsManager>().Get()->Clear();

	currentSceneID = scene_id;
	LPSCENE s = scenes[scene_id];
	CLocator<IHandleInput>().Get()->SetKeyHandler(s->GetKeyEventHandler());
	DebugOut(L"[INFO] Switching to scene KeyEventHandler\n");
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
	//mario = new CMario(100,100);
	//mario->SetPosition(10.0f, 100.0f);
	Load(L"mario-sample.txt");
	//LoadResources();
}


int CGame::GetCurrentSceneID()
{
	return currentSceneID;
}

LPSCENE CGame::GetCurrentScene()
{
	return scenes[currentSceneID];
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
			CLocator<IHandleInput>().Get()->ProcessKeyboard();
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;

}

void CGame::SetWidthHeight(int w, int h)
{
	screenWidth = w;
	screenHeight = h;
}




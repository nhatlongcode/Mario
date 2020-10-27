#pragma once
#include <d3dx9.h>
#include "MarioDefines.h"
#include "CWindow.h"
#include "CDirectX.h"
#include "CLocator.h"
#include "CGameObject.h"
#include "CTexturesManager.h"
#include "CAnimationsManager.h"
#include "CInput.h"
#include "CMario.h"
#include "CScene.h"

class CGame
{
private:
	static CGame* instance;
	void Update(DWORD dt);
	void Render();
	void LoadResources();
	void Load(LPCWSTR filePath);
	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);

	void SwitchScene(int scene_id);

	unordered_map<int, LPSCENE> scenes;
	int currentScene;

	CMario* mario;

	float cam_x = 0.0f;
	float cam_y = 0.0f;

	int screen_width;
	int screen_height;
	LPKEYEVENTHANDLER keyHandler;

public:
	static CGame* Instance();
	~CGame();
	void InitGame();
	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	int GetCurrentScene();

	int Run();
	int GetScreenWidth() { return screen_width; }
	int GetScreenHeight() { return screen_height; }
};


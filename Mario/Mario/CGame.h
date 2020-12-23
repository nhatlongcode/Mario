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
	
	int currentSceneID;
	DWORD dt;
	float timeScale;
	int screenWidth;
	int screenHeight;
	LPKEYEVENTHANDLER keyHandler;

public:
	static CGame* Instance();
	~CGame();
	void InitGame();
	
	int GetCurrentSceneID();
	LPSCENE GetCurrentScene();

	DWORD GetDeltaTime();
	float GetTimeScale();
	int Run();
	int GetScreenWidth() { return screenWidth; }
	int GetScreenHeight() { return screenHeight; }

	void SetWidthHeight(int w, int h);
};


#pragma once

#include <d3dx9.h>
#include "CKeyEventHandler.h"
#include "CMario.h"
#include "MarioController.h"
#include "CCanvas.h"
#include "CCamera.h"
class CScene
{
protected:
	
	int id;
	int alpha;
	CCamera* camera;
	CKeyEventHandler* keyHandler;
	MarioController marioController;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> onPlayerObjects;
	//shared_ptr<LPGAMEOBJECT> objects;
	//shared_ptr<LPGAMEOBJECT> coObjects;
	
	LPCWSTR sceneFilePath;
	LPCANVAS canvas;
	CMario* player;

public:
	CScene(int id, LPCWSTR filePath);
	bool debugMode;
	CKeyEventHandler* GetKeyEventHandler() { return keyHandler; }
	CMario* GetPlayer(int id = 0);
	void FadedAndSwitchScene(int id);
	void SetPlayer(int typeID, float posX = 0.0f, float posY = 0.0f);
	void AddGameObject(LPGAMEOBJECT go);
	void AddCoGameObject(LPGAMEOBJECT go);
	void RemoveGameObject(LPGAMEOBJECT go);
	void GetCamPos(float& cx, float& cy);
	CCamera* GetCamera();
	void AddUI(LPUI ui);

	virtual void SetAlpha(int alpha) = 0;
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void LogInfo() = 0;
};
typedef CScene* LPSCENE;


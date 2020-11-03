#pragma once

#include <d3dx9.h>
#include "CKeyEventHandler.h"
#include "CMario.h"
#include "MarioController.h"
#include "CCamera.h"

class CScene
{
protected:
	int id;
	CCamera* camera;
	CKeyEventHandler* keyHandler;
	MarioController marioController;
	LPCWSTR sceneFilePath;
	CMario* player;

public:
	CScene(int id, LPCWSTR filePath);

	CKeyEventHandler* GetKeyEventHandler() { return keyHandler; }
	CMario* GetPlayer();
	void SetPlayer(int typeID, float posX = 0.0f, float posY = 0.0f);
	void GetCamPos(float& cx, float& cy);
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void LogInfo() = 0;
};
typedef CScene* LPSCENE;
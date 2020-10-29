#pragma once

#include <d3dx9.h>
#include "CKeyEventHandler.h"
#include "CMario.h"
#include "MarioController.h"

class CScene
{
protected:
	int id;
	CKeyEventHandler* keyHandler;
	MarioController marioController;
	LPCWSTR sceneFilePath;
	CMario* player;

public:
	CScene(int id, LPCWSTR filePath);

	CKeyEventHandler* GetKeyEventHandler() { return keyHandler; }
	CMario* GetPlayer();
	void SetPlayer(int typeID, float posX = 0.0f, float posY = 0.0f);
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef CScene* LPSCENE;
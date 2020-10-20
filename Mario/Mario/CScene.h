#pragma once

#include <d3dx9.h>
#include "CKeyEventHandler.h"

class CScene
{
protected:
	CKeyEventHandler* key_handler;
	int id;
	LPCWSTR sceneFilePath;

public:
	CScene(int id, LPCWSTR filePath);

	CKeyEventHandler* GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef CScene* LPSCENE;
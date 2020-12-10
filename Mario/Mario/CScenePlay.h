#pragma once
#include "CGame.h"
#include "CScene.h"
#include "CMario.h"
#include "MarioController.h"
#include "CCanvas.h"
#include "CMap.h"
#include "CCamera.h"

class CScenePlay : public CScene
{
private:
	CSprite* testSprite;
	LPCANVAS canvas;
protected:				// A play scene has to have player, right? 
	CMap* map;
	void ParseSection_TEXTURES(string line);
	void ParseSection_SPRITES(string line);
	void ParseSection_ANIMATIONS(string line);
	void ParseSection_ANIMATION_SETS(string line);
	void ParseSection_OBJECTS(string line);
	void ParseSection_GROUNDS(string line);
	void ParseSection_GHOSTPLATFORM(string line);
	void ParseSection_UI(string line);


public:
	CScenePlay(int id, LPCWSTR filePath);

	void Load();
	void Update(DWORD dt);
	void Render();
	void Unload();
	void LogInfo();

	//friend class CPlayScenceKeyHandler;
};

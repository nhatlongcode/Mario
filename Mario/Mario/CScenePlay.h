#pragma once
#include "CGame.h"
#include "CScene.h"
#include "CMario.h"
#include "MarioController.h"
#include "CMap.h"
#include "CCamera.h"
#include "CText.h"

class CScenePlay : public CScene
{
private:

	CText* timeText;
	int gameTime;
protected:		
	int index, life, score, money, time;
	int startTime;
	CMap* map;
	void ParseSection_TEXTURES(string line);
	void ParseSection_SPRITES(string line);
	void ParseSection_ANIMATIONS(string line);
	void ParseSection_ANIMATION_SETS(string line);
	void ParseSection_OBJECTS(string line);
	void ParseSection_GROUNDS(string line);
	void ParseSection_GHOSTPLATFORM(string line);
	void ParseSection_FONTS(string line);


public:
	CScenePlay(int id, LPCWSTR filePath);

	void Load();
	void Update(DWORD dt);
	void Render();
	void Unload();
	void LogInfo();

	//friend class CPlayScenceKeyHandler;
};

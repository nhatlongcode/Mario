#pragma once
#include "CGame.h"
#include "CScene.h"
#include "CMario.h"
#include "MarioController.h"
#include "CMap.h"
#include "CCamera.h"
#include "CText.h"
#include "CGamePanel.h"

class CScenePlay : public CScene
{
private:

	int time, startTime, gameTime;
	CGamePanel* gamePanel;
	CMap* map; // tiled background

	void ParseSection_TEXTURES(string line);
	void ParseSection_MAP(string line);
	void ParseSection_SPRITES(string line);
	void ParseSection_ANIMATIONS(string line);
	void ParseSection_ANIMATION_SETS(string line);
	void ParseSection_OBJECTS(string line);
	void ParseSection_GROUNDS(string line);
	void ParseSection_GHOSTPLATFORM(string line);
	void ParseSection_FONTS(string line);
	void ParseSection_PIPE(string line);

public:
	CScenePlay(int id, LPCWSTR filePath);

	void SetAlpha(int alpha);
	void Load();
	void Update(DWORD dt);
	void Render();
	void Unload();
	void LogInfo();

	//friend class CPlayScenceKeyHandler;
};

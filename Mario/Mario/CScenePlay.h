#pragma once
#include "CGame.h"
#include "CScene.h"
#include "CMario.h"
#include "MarioController.h"
#include "CMap.h"
#include "CCamera.h"

class CScenePlay : public CScene
{
private:
	vector<LPGAMEOBJECT> coObjects;
protected:				// A play scene has to have player, right? 
	CMap* map;
	vector<LPGAMEOBJECT> objects;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_GROUNDS(string line);
	void _ParseSection_GHOSTPLATFORM(string line);


public:
	CScenePlay(int id, LPCWSTR filePath);

	void Load();
	void Update(DWORD dt);
	void Render();
	void Unload();
	void LogInfo();

	//friend class CPlayScenceKeyHandler;
};

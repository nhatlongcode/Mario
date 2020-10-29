#pragma once
#include "CGame.h"
#include "CScene.h"
#include "CMario.h"
#include "MarioController.h"

class CScenePlay : public CScene
{
protected:				// A play scene has to have player, right? 

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);


public:
	CScenePlay(int id, LPCWSTR filePath);

	void Load();
	void Update(DWORD dt);
	void Render();
	void Unload();

	//friend class CPlayScenceKeyHandler;
};

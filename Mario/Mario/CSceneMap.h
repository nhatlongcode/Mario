#pragma once
#include "CScene.h"
#include "CMap.h"
#include "CMarioIcon.h"

class CSceneMap : public CScene
{
private:
	CMap* map;
	bool isMoveable;
	CMarioIcon* marioIcon;
	int** dataPath;
	
	int col, row;
public:
	CSceneMap(int id, LPCWSTR filePath);
	void PlayerMove(int direction);
	void PlayerScelect();

	void ParseSection_TEXTURES(string line);
	void ParseSection_MAP(string line);
	void ParseSection_PATH(string line, int rowIndex);
	void ParseSection_PATHINFO(string line);
	void ParseSection_SPRITES(string line);
	void ParseSection_ANIMATIONS(string line);
	void ParseSection_ANIMATION_SETS(string line);
	void ParseSection_OBJECTS(string line);
	void ParseSection_MAPSELECTABLE(string line);
	void ParseSection_FONTS(string line);


	virtual void Load() override;
	virtual void Unload() override;
	virtual void Update(DWORD dt) override;
	virtual void Render() override;
	virtual void LogInfo() override;
};
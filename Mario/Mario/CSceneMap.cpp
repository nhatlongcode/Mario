#include "CSceneMap.h"
#include "CSceneMapKeyHandler.h"
#include "CLocator.h"
#include "IAnimSetsManager.h"
#include "IAnimsManager.h"
#include "IFontManager.h"
#include <iostream>
#include <string>
#include <fstream>

CSceneMap::CSceneMap(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	keyHandler = new CSceneMapKeyHandler(this);

}

void CSceneMap::PlayerMove(int direction)
{
}

void CSceneMap::ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());
	CLocator<ITexsManager>().Get()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));

}

void CSceneMap::ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	map = new CMap(texID, path.c_str());
}

void CSceneMap::ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 9) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int left = atoi(tokens[1].c_str());
	int top = atoi(tokens[2].c_str());
	int width = atoi(tokens[3].c_str());
	int height = atoi(tokens[4].c_str());
	int scaleX = atoi(tokens[5].c_str());
	int scaleY = atoi(tokens[6].c_str());
	int xPivot = atoi(tokens[7].c_str());
	int texID = atoi(tokens[8].c_str());

	LPDIRECT3DTEXTURE9 tex = CLocator<ITexsManager>().Get()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CLocator<ISpritesManager>().Get()->Add(ID, left, top, width, height, scaleX, scaleY, xPivot, tex);
}

void CSceneMap::ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		//DebugOut(L"i: %d\n", tokens.size());
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}
	CLocator<IAnimsManager>().Get()->Add(ani_id, ani);
}

void CSceneMap::ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMSET set = new CAnimSet();

	LPANIMATIONS anims = CLocator<IAnimsManager>().Get();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION anim = anims->Get(ani_id);
		set->push_back(anim);
	}

	CLocator<IAnimSetsManager>().Get()->Add(ani_set_id, set);
}

void CSceneMap::ParseSection_OBJECTS(string line)
{
}

void CSceneMap::ParseSection_FONTS(string line)
{
	{
		vector<string> tokens = split(line);

		if (tokens.size() < 6) return;
		int font, ascii, t, l, w, h;
		font = atoi(tokens[0].c_str());
		ascii = atoi(tokens[1].c_str());
		t = atoi(tokens[2].c_str());
		l = atoi(tokens[3].c_str());
		w = atoi(tokens[4].c_str());
		h = atoi(tokens[5].c_str());
		CLocator<IFontManager>().Get()->AddFont(font, ascii, t, l, w, h);
	}
}

void CSceneMap::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[FONTS]")
		{
			section = SCENE_SECTION_FONTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		switch (section)
		{
			case SCENE_SECTION_TEXTURES: ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_MAP: ParseSection_MAP(line); break;
			case SCENE_SECTION_SPRITES: ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_FONTS: ParseSection_FONTS(line); break;
		}
	}
	map = new CMap(0, L"map2.txt");
}

void CSceneMap::Unload()
{
}

void CSceneMap::Update(DWORD dt)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
}

void CSceneMap::Render()
{
	map->Render();
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();

	}
}

void CSceneMap::LogInfo()
{
}

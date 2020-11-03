#include "CScenePlay.h"
#include "CScenePlayKeyHandler.h"
#include "CAnimationSetsManager.h"
#include "CGoomba.h"
#include "CBrick.h"
#include "CGame.h"
#include <iostream>
#include <fstream>

void CScenePlay::_ParseSection_TEXTURES(string line)
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

void CScenePlay::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 8) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int left = atoi(tokens[1].c_str());
	int top = atoi(tokens[2].c_str());
	int width = atoi(tokens[3].c_str());
	int height = atoi(tokens[4].c_str());
	int scaleX = atoi(tokens[5].c_str());
	int scaleY = atoi(tokens[6].c_str());
	int texID = atoi(tokens[7].c_str());

	LPDIRECT3DTEXTURE9 tex = CLocator<ITexsManager>().Get()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CLocator<ISpritesManager>().Get()->Add(ID, left, top, width, height, scaleX, scaleY, tex);
}

void CScenePlay::_ParseSection_ANIMATIONS(string line)
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

void CScenePlay::_ParseSection_ANIMATION_SETS(string line)
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

void CScenePlay::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	LPANIMATIONSETS animSets = CLocator<IAnimSetsManager>().Get();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario();
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	//case OBJECT_TYPE_KOOPAS: obj = new CKoopas(); break;
	/*case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;*/
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	obj->SetAnimationSet(ani_set_id);
	objects.push_back(obj);
}

CScenePlay::CScenePlay(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	keyHandler = new CScenePlayKeyHandler(this);
}

void CScenePlay::Load()
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
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();
	
	map = new CMap(1, L"map.txt");
	
	marioController.Init();
	SetPlayer(MARIO_TYPE_SMALL, 300.0f, 100.0f);
	
	camera = new CCamera(CGame::Instance()->GetScreenWidth(), CGame::Instance()->GetScreenHeight());
	camera->SetOffSet(CAMERA_OFFSET_LEFT,
		CAMERA_OFFSET_RIGHT,
		CAMERA_OFFSET_TOP,
		CAMERA_OFFSET_BOT);
	camera->SetBorder(CAMERA_BORDER_LEFT,
		CAMERA_BORDER_RIGHT,
		CAMERA_BORDER_TOP,
		CAMERA_BORDER_BOT);
	camera->SetPlayer(this->player);
	
	//objects.push_back(player);
	if (player == NULL) DebugOut(L"PLAYER NULL");

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CScenePlay::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	if (player == NULL) return;

	player->Update(dt, &coObjects);
	camera->Update();
}

void CScenePlay::Render()
{
	map->Render();
	//CLocator<ISpritesManager>().Get()->Get(441)->Draw(300, 300);
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	player->Render();
	
}

void CScenePlay::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CScenePlay::LogInfo()
{
	float cx, cy, px, py;
	camera->GetCamPos(cx, cy);
	player->GetPosition(px, py);
	DebugOut(L"----------------------------------------\n");
	DebugOut(L"Camera pos X: %.2f\n", cx);
	DebugOut(L"Camera pos Y: %.2f\n", cy);
	DebugOut(L"Player pos X: %.2f\n", px);
	DebugOut(L"Player pos Y: %.2f\n", py);
	DebugOut(L"Screen width: %d\n", CGame::Instance()->GetScreenWidth());
	DebugOut(L"Screen height: %d\n", CGame::Instance()->GetScreenHeight());
	DebugOut(L"----------------------------------------\n");
}

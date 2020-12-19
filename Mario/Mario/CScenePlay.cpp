#include "CScenePlay.h"
#include "CScenePlayKeyHandler.h"
#include "CAnimationSetsManager.h"
#include "CFontManager.h"
#include "CText.h"
#include "CLocator.h"
#include "CGoomba.h"
#include "CKoopas.h"
#include "CBrick.h"
#include "CQuestionBrick.h"
#include "CGround.h"
#include "CGhostPlatform.h"
#include "CGame.h"
#include <iostream>
#include <fstream>

void CScenePlay::ParseSection_TEXTURES(string line)
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

void CScenePlay::ParseSection_SPRITES(string line)
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

void CScenePlay::ParseSection_ANIMATIONS(string line)
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

void CScenePlay::ParseSection_ANIMATION_SETS(string line)
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

void CScenePlay::ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);


	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int animSetID = atoi(tokens[3].c_str());

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
	case OBJECT_TYPE_KOOPAS: obj = new CKoopas(); break;

	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	obj->SetAnimationSet(animSetID);
	objects.push_back(obj);
}

void CScenePlay::ParseSection_GROUNDS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 4) return;

	float x, y, w, h;
	x = atoi(tokens[0].c_str());
	y = atoi(tokens[1].c_str());
	w = atoi(tokens[2].c_str());
	h = atoi(tokens[3].c_str());

	CGameObject* ground = new CGround();
	ground->SetPosition(x, y);
	ground->SetBoundingBox(w, h);


	objects.push_back(ground);
}

void CScenePlay::ParseSection_GHOSTPLATFORM(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return;
	int type;
	float x, y, w, h;
	x = atoi(tokens[0].c_str());
	y = atoi(tokens[1].c_str());
	w = atoi(tokens[2].c_str());
	h = atoi(tokens[3].c_str());
	type = atoi(tokens[4].c_str());
	

	CGameObject* ghost = new CGhostPlatform();
	ghost->SetPosition(x, y);
	ghost->SetBoundingBox(w, h);
	switch (type)
	{
		case 0: 
			ghost->SetTag(ObjectTag::GhostPlatform);
			break;
		case 1: 
			ghost->SetTag(ObjectTag::Solid);
			break;
	}


	objects.push_back(ghost);
}

void CScenePlay::ParseSection_FONTS(string line)
{

}


CScenePlay::CScenePlay(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	keyHandler = new CScenePlayKeyHandler(this);
	CGame::Instance()->SetWidthHeight(GAME_WIDTH, GAME_HEIGHT);
	map = NULL;
	camera = new CCamera(CGame::Instance()->GetScreenWidth(), CGame::Instance()->GetScreenHeight());
	camera->SetOffSet(CAMERA_OFFSET_LEFT,
		CAMERA_OFFSET_RIGHT,
		CAMERA_OFFSET_TOP,
		CAMERA_OFFSET_BOT);
	camera->SetBorder(CAMERA_BORDER_LEFT,
		CAMERA_BORDER_RIGHT,
		CAMERA_BORDER_TOP,
		CAMERA_BORDER_BOT);

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
		if (line == "[GROUNDS]") {
			section = SCENE_SECTION_GROUNDS; continue;
		}
		if (line == "[GHOSTPLATFORM]") {
			section = SCENE_SECTION_GHOSTPLATFORM; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_GROUNDS: ParseSection_GROUNDS(line); break;
		case SCENE_SECTION_GHOSTPLATFORM: ParseSection_GHOSTPLATFORM(line); break;
		case SCENE_SECTION_UI: ParseSection_GHOSTPLATFORM(line); break;
		}
	}

	f.close();
	map = new CMap(1, L"map.txt");
	marioController.Init();
	SetPlayer(MARIO_TYPE_SMALL, 300.0f, 100.0f);
	camera->SetPlayer(this->player);
	
	CGameObject* brickTest = new CQuestionBrick();
	brickTest->SetPosition(300, 1050);
	objects.push_back(brickTest);
	if (player == NULL) DebugOut(L"PLAYER NULL");

	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	auto tex = CLocator<ITexsManager>().Get()->Get(5);

	CLocator<IFontManager>().Get()->AddFont(MARIO_FONT_ID, 48, 72, 96, 24, 24);
	CText* text = new CText("0", MARIO_FONT_ID);
	
	text->SetPosition(300.0f, 300.0f);
	canvas->Add(text);
	//LPUI ui = new CUIElement(0, 20, 375, 725, 120, 1, 1, tex);
	//ui->SetPosition(0, 578);
	//canvas->Add(ui);


	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CScenePlay::Update(DWORD dt)
{

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	if (player == NULL) return;

	player->Update(dt, &coObjects);
	camera->Update();
	canvas->Update(dt);
}

void CScenePlay::Render()
{
	map->Render();
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
		if (debugMode) objects[i]->RenderCollisionBox();

	}
	player->Render();
	if (debugMode) player->RenderCollisionBox();
	float camX, camY;
	CGame::Instance()->GetCurrentScene()->GetCamPos(camX, camY);
	canvas->Render();
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
	DebugOut(L"Player collision: %d\n", player->IsCollisionEnabled);
	DebugOut(L"Screen width: %d\n", CGame::Instance()->GetScreenWidth());
	DebugOut(L"Screen height: %d\n", CGame::Instance()->GetScreenHeight());
	DebugOut(L"----------------------------------------\n");
}

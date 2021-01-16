#include "CScene.h"

CScene::CScene(int id, LPCWSTR filePath)
{
	this->id = id;
	debugMode = false;
	this->sceneFilePath = filePath;
	canvas = new CCanvas();
}

CMario* CScene::GetPlayer(int id)
{
	if (id == 0) return player;
	else return marioController.GetMario(id);
}

void CScene::FadedAndSwitchScene(int id)
{
}

void CScene::SetPlayer(int typeID, float posX, float posY)
{
	CMario* newPlayer = marioController.GetMario(typeID, posX, posY);
	if (player != NULL)
	{
		float x, y, vx, vy;
		int nx;
		int state;
		player->GetPosition(x, y);
		player->GetDirection(nx);
		player->GetState(state);
		player->GetSpeed(vx, vy);
		player->Reset();

		newPlayer->SetPosition(posX, posY);
		newPlayer->SetDirection(nx);
		newPlayer->SetState(state);
		newPlayer->SetSpeed(vx, vy);
	}


	player = newPlayer;
	if (camera != NULL) camera->SetPlayer(newPlayer);
	DebugOut(L"Set to new mario ID: %d\n", typeID);
}

void CScene::AddGameObject(LPGAMEOBJECT go)
{
	objects.push_back(go);
	coObjects.push_back(go);
}

void CScene::AddCoGameObject(LPGAMEOBJECT go)
{
	coObjects.push_back(go);
}

void CScene::RemoveGameObject(LPGAMEOBJECT go)
{
	auto pos = std::find(objects.begin(), objects.end(), go);
	if (pos != objects.end()) objects.erase(pos);

	auto pos2 = std::find(coObjects.begin(), coObjects.end(), go);
	if (pos2 != coObjects.end()) coObjects.erase(pos2);
}

void CScene::GetCamPos(float& cx, float& cy)
{
	float x, y;
	camera->GetCamPos(x, y);
	cx = x;
	cy = y;
}

CCamera* CScene::GetCamera()
{
	return camera;
}

void CScene::AddUI(LPUI ui)
{
	canvas->Add(ui);
}


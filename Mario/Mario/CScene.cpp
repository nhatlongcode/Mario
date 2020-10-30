#include "CScene.h"

CScene::CScene(int id, LPCWSTR filePath)
{
	this->id = id;
	this->sceneFilePath = filePath;
}

CMario* CScene::GetPlayer()
{
	return player;
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

		newPlayer->SetPosition(x, y);
		newPlayer->SetDirection(nx);
		newPlayer->SetState(state);
		newPlayer->SetSpeed(vx, vy);
	}


	player = newPlayer;
	DebugOut(L"Set to new mario ID: %d\n", typeID);
}

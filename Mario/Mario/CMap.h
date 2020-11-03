#pragma once
#include <d3dx9.h>
#include "CSprite.h"
#include "CTileMap.h"

class CMap
{
private:
	int col, row;
	vector<CTileMap*> data;
	void Load(int texID, LPCWSTR path);
	void ParseSectionSize(string line);
	void ParseSectionData(string line, int rowCount);
	unordered_map<int, LPSPRITE> sprites;
public:
	CMap(int texID, LPCWSTR path);
	void Render();
};
#include "CMap.h"
#include "CLocator.h"
#include "CTexturesManager.h"
#include "ISpritesManager.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream> 


void CMap::Load(int texID, LPCWSTR path)
{
	if (path == NULL)
	{
		return;
	}

	LPDIRECT3DTEXTURE9 tex = CLocator<ITexsManager>().Get()->Get(texID);
	D3DSURFACE_DESC desc;
	tex->GetLevelDesc(0, &desc);
	int top = 0, left = 0, id = 1;
	while (top < desc.Height)
	{
		while (left < desc.Width)
		{
			//LPSPRITE sprite = new CSprite(id, left, top, 48, 48, 1, 1, tex);
			//sprites[id] = sprite;
			CLocator<ISpritesManager>().Get()->Add(id, left, top, 48, 48, 1, 1, 0, tex);
			left += 48;
			id++;
		}
		top += 48;
		left = 0;
	}



	ifstream f;
	f.open(path);

	char str[MAX_SCENE_LINE];
	int row = -1;
	int section = MAP_SECTION_UNKNOWN;
	while (f.getline(str, MAX_SCENE_LINE))
	{
		//DebugOut(L"%d\n", section);
		string line(str);
		if (line == "[SIZE]")
		{
			section = MAP_SECTION_SIZE;
			continue;
		}
		else if (line == "[DATA]")
		{
			section = MAP_SECTION_DATA;
			continue;
		}

		switch (section)
		{
			case MAP_SECTION_SIZE:
			{
				ParseSectionSize(line);
				break;
			}
			case MAP_SECTION_DATA:
			{
				row++;
				ParseSectionData(line, row);
				break;
			}
		}
	}

	f.close();

}

void CMap::ParseSectionSize(string line)
{
	vector<string> tokens = split(line);
	//if (tokens.size() < 2) return;
	row = atoi(tokens[0].c_str());
	col = atoi(tokens[1].c_str());
}

void CMap::ParseSectionData(string line, int rowCount)
{
	CTileMap* tile;
	int id;
	vector<string> tokens = split(line);
	if (tokens.size() < col) return;
	for (int i = 0; i < col; i++)
	{
		id = atoi(tokens[i].c_str());
		if (id != 0)
		{
			tile = new CTileMap(i * 48, rowCount * 48, id);
			data.push_back(tile);
		}
	}
}

CMap::CMap(int texID, LPCWSTR path)
{
	Load(texID, path);
	alpha = 255;
}

void CMap::SetAlpha(int alpha)
{
	this->alpha = alpha;
	for (int i = 0; i < data.size(); i++)
	{
		data[i]->SetAlpha(this->alpha);
	}
}

void CMap::Render()
{
	for (int i = 0; i < data.size(); i++)
	{

		data[i]->Render();
	}
}

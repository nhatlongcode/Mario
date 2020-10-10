#ifndef CSPRITEMANAGER_H
#define CSPRITEMANAGER_H

#include "CSprite.h"
#include <d3dx9.h>
#include <unordered_map>

class CSpritesManager
{
private:
	std::unordered_map<int, LPSPRITE> sprites;
public:
	void Init();
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
};
#endif // !CSPRITEMANAGER_H


#pragma once
#include "CLocator.h"
#include "CDirectX.h"
#include "MarioDefines.h"
#include "ITexsManager.h"
#include <unordered_map>
#include <d3dx9.h>
#include "Utils.h"

class CTexturesManager : public ITexsManager
{
private:
    std::unordered_map<int, LPDIRECT3DTEXTURE9> textures;
public: 
    void Add(int id, LPCWSTR path, D3DCOLOR transColor);
    LPDIRECT3DTEXTURE9 Get(int id);
    void Clear();
};




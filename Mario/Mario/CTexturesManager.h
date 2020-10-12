#pragma once
#include "CLocator.h"
#include "CDirectX.h"
#include "MarioDefines.h"
#include <unordered_map>
#include <d3d9.h>
#include <d3dx9.h>
#include "Utils.h"

class CTexturesManager
{
private:
    std::unordered_map<std::string, LPDIRECT3DTEXTURE9> textures;
    LPDIRECT3DTEXTURE9 CreateTexture(LPCWSTR path);
public: 
    void Add(std::string id, LPCWSTR path, D3DCOLOR transColor);
    LPDIRECT3DTEXTURE9 Get(std::string id);
};

typedef CTexturesManager* LPTEXTURES;


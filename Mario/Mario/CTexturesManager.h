#ifndef CTEXTURESMANAGER_H
#define CTEXTURESMANAGER_H
#endif // !CTEXTURESMANAGER_H

#include "CAbstractService.h"
#include "CLocator.h"
#include "CDirectX.h"
#include "MarioDefines.h"
#include <unordered_map>
#include <d3d9.h>
#include <d3dx9.h>
#include "Utils.h"

class CTexturesManager : public CAbstractService
{
private:
    std::unordered_map<std::string, LPDIRECT3DTEXTURE9> textures;
    LPDIRECT3DTEXTURE9 CreateTexture(LPCWSTR path);
public: 
    void Init();
    void Add(std::string id, LPCWSTR path, D3DCOLOR transColor);
    LPDIRECT3DTEXTURE9 Get(std::string id);
};


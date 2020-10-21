#pragma once
#include <d3dx9.h>
class ITexsManager
{
public:
	virtual void Add(int id, LPCWSTR path, D3DCOLOR transColor) = 0;
	virtual LPDIRECT3DTEXTURE9 Get(int id) = 0;
	virtual void Clear() = 0;
};


typedef ITexsManager* LPTEXTURES;
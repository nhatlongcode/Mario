#include "CTexturesManager.h"

void CTexturesManager::Add(int id, LPCWSTR path, D3DCOLOR transColor)
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;

	HRESULT result = D3DXGetImageInfoFromFile(path, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", path);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = CLocator<IDirectX>().Get()->Device();

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		path,						// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] CreateTextureFromFile failed. File: %s\n", path);
		return;
	}

	DebugOut(L"[INFO] Texture loaded Ok: %s \n", path);
	textures[id] = texture;
}

LPDIRECT3DTEXTURE9 CTexturesManager::Get(int id)
{
	return textures[id];
}

void CTexturesManager::Clear()
{
	for (auto x : textures)
	{
		LPDIRECT3DTEXTURE9 tex = x.second;
		if (tex != NULL) tex->Release();
	}

	textures.clear();
}

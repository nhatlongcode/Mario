#include "CTexturesManager.h"

LPDIRECT3DTEXTURE9 CTexturesManager::CreateTexture(LPCWSTR path)
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;

	auto result = D3DXGetImageInfoFromFileW(texPath, &info);
	auto d3ddev = Game::GetInstance().GetD3DDevice();

	if (result != D3D_OK) return NULL;

	result = D3DXCreateTextureFromFileExW(
		d3ddev, texPath, info.Width, info.Height,
		1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		&info, NULL, &texture
	);

	if (result != D3D_OK) return NULL;
	return texture;
}

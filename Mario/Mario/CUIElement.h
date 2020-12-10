#pragma once
#include <d3dx9.h>
#include <unordered_map>
#include "CLocator.h"
#include "CDirectX.h"


class CUIElement
{
private:
	float x, y;
	int id;
	int alpha;
	int left;
	int top;
	int width;
	int height;
	int scaleX;
	int scaleY;
	LPDIRECT3DTEXTURE9 texture;
public:
	bool IsEnable;
	CUIElement(int id, int left, int top, int width, int height, int scaleX, int scaleY, LPDIRECT3DTEXTURE9 texture);
	
	void SetPosition(float x, float y);
	void GetPosition(float& x, float& y);

	float GetX();
	float GetY();

	void SetAlpha(int alpha);
	float GetAlpha();

	void Render();
	void Update(DWORD dt);
};

typedef CUIElement* LPUI;
#pragma once
#include "CUIElement.h"

class CImage : public CUIElement
{
private:
	int left, top, width, height;
	float scaleX, scaleY;
	LPDIRECT3DTEXTURE9 texture;
public:
	CImage(int left = 0, int top = 0, int width = 0, int height = 0, float scaleX = 0.0f, float scaleY = 0.0f, LPDIRECT3DTEXTURE9 tex = nullptr);
	void Render() override;
};
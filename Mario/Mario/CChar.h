#pragma once
#include "CUIElement.h"

class CChar : public CUIElement
{
private:
	int left, top, width, height;
	float scaleX, scaleY;
	LPDIRECT3DTEXTURE9 texture;
public:
	CChar(int left, int top, int width, int height, float scaleX, float scaleY, LPDIRECT3DTEXTURE9 texture);
	int GetWidth();
	void Render() override;
};
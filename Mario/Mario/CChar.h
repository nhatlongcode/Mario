#pragma once
#include "CUIElement.h"

class CChar : public CUIElement
{
private:
	int left, top, width, height, scaleX, scaleY;
	LPDIRECT3DTEXTURE9 texture;
public:
	CChar(int left, int top, int width, int height, int scaleX, int scaleY, LPDIRECT3DTEXTURE9 texture);
	int GetWidth();
	void Render() override;
};
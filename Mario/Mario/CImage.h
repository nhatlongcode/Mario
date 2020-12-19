#pragma once
#include "CUIElement.h"

class CImage : public CUIElement
{
private:
	int left, top, width, height, scaleX, scaleY;
	LPDIRECT3DTEXTURE9 texture;
public:
	CImage(int left, int top, int width, int height, int scaleX, int scaleY, LPDIRECT3DTEXTURE9 tex);
	void Render() override;
};
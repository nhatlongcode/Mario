#include "CChar.h"

CChar::CChar(int id, int left, int top, int width, int height, int size, LPDIRECT3DTEXTURE9 texture)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->size = size;
	this->texture = texture;
	x = y = 0.0f;
}

void CChar::Render()
{
}

void CChar::SetSize(int size)
{
	this->size = size;
}

void CChar::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

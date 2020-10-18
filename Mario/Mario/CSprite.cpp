#include "CSprite.h"

CSprite::CSprite(int id, int left, int top, int width, int height, Vector2 scale, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->scale = scale;
	this->texture = tex;
}

void CSprite::Draw(float x, float y, int alpha)
{
	LPD3DXSPRITE spriteHandler = CLocator<IDirectX>().Get()->SpriteHandler();
	RECT r;
	r.left = left;
	r.top = top;
	r.right = left + width;
	r.bottom = top + height;
	

	D3DXMATRIX oldMatrix, newMatrix;
	spriteHandler->GetTransform(&oldMatrix);

	D3DXMatrixTransformation2D(&newMatrix, &Vector2(x,y), 0, &scale, NULL, 0.0f, NULL);
	newMatrix = oldMatrix * newMatrix;

	spriteHandler->SetTransform(&newMatrix);
	spriteHandler->Draw(texture, &r, &Vector3((float)width/2, (float)height/2, 0), &Vector3(x, y, 0), D3DCOLOR_ARGB(alpha, 255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix);

}

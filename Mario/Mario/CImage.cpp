#include "CImage.h"
#include "CGame.h"

CImage::CImage(int left, int top, int width, int height, float scaleX, float scaleY, LPDIRECT3DTEXTURE9 tex)
{
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->texture = tex;
	alpha = 255;
}

void CImage::Render()
{
	LPD3DXSPRITE spriteHandler = CLocator<IDirectX>().Get()->SpriteHandler();
	RECT r;
	r.left = left;
	r.top = top;
	r.right = left + width;
	r.bottom = top + height;

	float camX, camY;
	CGame::Instance()->GetCurrentScene()->GetCamPos(camX, camY);
	Vector3 p((int)(x), (int)(y), 0);

	Vector2 scale = Vector2(scaleX, scaleY);
	D3DXMATRIX oldMatrix, newMatrix;
	spriteHandler->GetTransform(&oldMatrix);

	D3DXMatrixTransformation2D(&newMatrix, &Vector2(x, y), 0, &scale, NULL, 0.0f, NULL);
	newMatrix = oldMatrix * newMatrix;
	spriteHandler->SetTransform(&newMatrix);
	spriteHandler->Draw(texture, &r, &Vector3(0, 0, 0), &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix);
}

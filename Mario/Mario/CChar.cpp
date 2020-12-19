#include "CChar.h"
#include "CGame.h"
#include "CLocator.h"
#include "IFontManager.h"



CChar::CChar(int left, int top, int width, int height, int scaleX, int scaleY, LPDIRECT3DTEXTURE9 texture)
{
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->texture = texture;
}

int CChar::GetWidth()
{
	return width;
}

void CChar::Render()
{
	LPD3DXSPRITE spriteHandler = CLocator<IDirectX>().Get()->SpriteHandler();
	RECT r;
	r.left = left;
	r.top = top;
	r.right = left + width;
	r.bottom = top + height;

	float camX, camY, w, h;
	w = CGame::Instance()->GetScreenWidth();
	h = CGame::Instance()->GetScreenHeight();

	CGame::Instance()->GetCurrentScene()->GetCamPos(camX, camY);
	//Vector3 p(x - camX,y - camY, 0);
	Vector3 p((int)(x - camX), (int)(y - camY), 0);

	Vector2 scale = Vector2(scaleX, scaleY);
	//camX *= scale.x;
	//camY *= scale.y;
	D3DXMATRIX oldMatrix, newMatrix;
	spriteHandler->GetTransform(&oldMatrix);

	D3DXMatrixTransformation2D(&newMatrix, &Vector2(p.x, p.y), 0, &scale, NULL, 0.0f, NULL);
	newMatrix = oldMatrix * newMatrix;

	spriteHandler->SetTransform(&newMatrix);
	spriteHandler->Draw(texture, &r, &Vector3(0,0,0), &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix);
}

#include "CUIElement.h"
#include "CGame.h"

CUIElement::CUIElement(int id, int left, int top, int width, int height, int scaleX, int scaleY, LPDIRECT3DTEXTURE9 texture)
{
	x = y = 0.0f;
	alpha = 255;
	IsEnable = true;
	this->id = id;
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->texture = texture;
}

void CUIElement::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CUIElement::GetPosition(float& x, float& y)
{
	x = this->x;
	y = this->y;
}

float CUIElement::GetX()
{
	return x;
}

float CUIElement::GetY()
{
	return y;
}

void CUIElement::SetAlpha(int alpha)
{
	this->alpha = alpha;
}

float CUIElement::GetAlpha()
{
	return alpha;
}

void CUIElement::Render()
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
	spriteHandler->Draw(texture, &r, &Vector3(0,0,0), &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix);
}

void CUIElement::Update(DWORD dt)
{
	DebugOut(L"asdad\n");
}

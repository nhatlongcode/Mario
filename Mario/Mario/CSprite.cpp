#include "CSprite.h"
#include "CGame.h"

CSprite::CSprite(int id, int left, int top, int width, int height, int scaleX, int scaleY, int xPivot, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->xPivot = xPivot;
	this->texture = tex;
}

void CSprite::Draw(float x, float y, int direction, int alpha)
{
	LPD3DXSPRITE spriteHandler = CLocator<IDirectX>().Get()->SpriteHandler();
	RECT r;
	r.left = left;
	r.top = top;
	r.right = left + width;
	r.bottom = top + height;
	
	float camX, camY;
	CGame::Instance()->GetCurrentScene()->GetCamPos(camX, camY);
	//if (x - camX < 0 - 100.0f) return;
	//Vector3 p(x - camX,y - camY, 0);
	Vector3 p((int)(x - camX),(int)(y - camY), 0);

	Vector2 scale = Vector2(scaleX * direction, scaleY);
	//camX *= scale.x;
	//camY *= scale.y;
	D3DXMATRIX oldMatrix, newMatrix;
	spriteHandler->GetTransform(&oldMatrix);

	D3DXMatrixTransformation2D(&newMatrix, &Vector2(p.x,p.y), 0, &scale, NULL, 0.0f, NULL);
	newMatrix = oldMatrix * newMatrix;

	Vector3 p2((int)p.x, (int)p.y, 0);
	spriteHandler->SetTransform(&newMatrix);
	spriteHandler->Draw(texture, &r, &Vector3((int)width/2 + xPivot, (int)height/2, 0), &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix);

}

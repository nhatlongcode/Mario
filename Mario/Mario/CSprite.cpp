#include "CSprite.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

void CSprite::Draw(float x, float y, int alpha)
{
	RECT r;
	r.left = left;
	r.top = top;
	r.bottom = bottom;
	r.right = right;
	
	D3DXVECTOR3 p(x,y,0);

	CLocator::Instance()->Get<CDirectX>()->SpriteHandler()->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));

}

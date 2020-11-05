#include <algorithm>
#include "CGameObject.h"
#include "CLocator.h"
#include "IAnimSetsManager.h"
#include "IDirectX.h"
#include "CLocator.h"
#include "ITexsManager.h"
#include "CGame.h"

void CGameObject::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CGameObject::SetDirection(int nx)
{
	this->nx = nx;
}

void CGameObject::SetState(int state)
{
	this->state = state;
}


LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT other)
{
	float sl, st, sr, sb;		// static object bbox -> other
	float ml, mt, mr, mb;		// moving object bbox -> this
	float t, nx, ny;
	DWORD dt = CGame::Instance()->GetDeltaTime();

	this->GetBoundingBox(sl, st, sr, sb);
	other->GetBoundingBox(ml, mt, mr, mb);

	float svx, svy;
	other->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = rdx > 0 ? ml : ml + rdx;
	float bt = rdy > 0 ? mt : mt + rdy;
	float br = rdx > 0 ? mr + rdx : mr;
	float bb = rdy > 0 ? mb + rdy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return nullptr;


	if (rdx == 0 && rdy == 0) return nullptr;		// moving object is not moving > obvious no collision

	if (rdx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (rdx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (rdy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (rdx == 0)
	{
		tx_entry = -999999.0f;
		tx_exit = 999999.0f;
	}
	else
	{
		tx_entry = dx_entry / rdx;
		tx_exit = dx_exit / rdx;
	}

	if (rdy == 0)
	{
		ty_entry = -99999.0f;
		ty_exit = 99999.0f;
	}
	else
	{
		ty_entry = dy_entry / rdy;
		ty_exit = dy_exit / rdy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return nullptr;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return nullptr; //???

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		rdx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		rdy > 0 ? ny = -1.0f : ny = 1.0f;
	}

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, rdx, rdy, other);
	return e;
}

CGameObject::CGameObject()
{
	IsCollisionEnabled = true;
	nx = 1;
	vx = vy = 0;
	x = y = 0;
}

void CGameObject::SetSpeedX(float vx)
{
	this->vx = vx;
}

void CGameObject::SetSpeedY(float vy)
{
	this->vy = vy;
}

void CGameObject::CheckCollision(vector<LPGAMEOBJECT>* coObjects)
{
	if (!IsCollisionEnabled) return;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f && e != nullptr) // co va cham
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);

	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;

	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);

	// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
	if (rdx != 0 && rdx != dx)
		x += nx * abs(rdx);

	// block every object first!
	x += min_tx * dx + nx * 0.4f;
	y += min_ty * dy + ny * 0.4f;

	if (nx != 0) vx = 0;
	if (ny != 0) vy = 0;

	for each (LPCOLLISIONEVENT coEvent in coEventsResult)
	{
		OnCollisionEnter(coEvent);
	}
}

void CGameObject::RenderCollisionBox()
{
	auto tex = CLocator<ITexsManager>().Get()->Get(10);
	if (tex == NULL) DebugOut(L"NULL\n");
	RECT bbRect;
	bbRect.left = x;
	bbRect.top = y;
	bbRect.right = x + bboxWidth;
	bbRect.bottom = y + bboxHeight;

	DebugOut(L"width %.2f\n",x);
	float cx, cy;
	CGame::Instance()->GetCurrentScene()->GetCamPos(cx, cy);
	Vector2 pos;
	pos.x = trunc(x - cx);
	pos.y = trunc(y - cy);
	LPD3DXSPRITE spriteHandler = CLocator<IDirectX>().Get()->SpriteHandler();
	spriteHandler->Draw(tex, &bbRect, &D3DXVECTOR3(bboxWidth * 0.5f, bboxHeight * 0.5f, 0), &D3DXVECTOR3(pos.x, pos.y, 0), D3DCOLOR_ARGB(32, 255, 255, 255));
}

void CGameObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + bboxWidth;
	b = y + bboxHeight;
}

void CGameObject::OnCollisionEnter(LPCOLLISIONEVENT other)
{
}

void CGameObject::SetBoundingBox(float width, float height)
{
	bboxWidth = width;
	bboxHeight = height;
}

void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION anim = CLocator<IAnimsManager>().Get()->Get(aniId);
	animSet->push_back(anim);
}

void CGameObject::SetAnimationSet(int animSetID)
{
	this->animSet = CLocator<IAnimSetsManager>().Get()->Get(animSetID);
}




void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	dx = vx * dt;
	dy = vy * dt;
	x += dx;
	y += dy;
/*
	DebugOut(L"x: %.2f", x);
	DebugOut(L"y: %.2f\n", y);
	DebugOut(L"camX: %.2f", camX);
	DebugOut(L"camY: %.2f\n", camY);
*/
}




CGameObject::~CGameObject()
{
}
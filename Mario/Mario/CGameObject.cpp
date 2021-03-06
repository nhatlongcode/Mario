#include <algorithm>
#include "CGameObject.h"
#include "CLocator.h"
#include "IAnimSetsManager.h"
#include "IDirectX.h"
#include "CLocator.h"
#include "CGhostPlatform.h"
#include "ITexsManager.h"
#include "CGame.h"

void CGameObject::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CGameObject::SetAlpha(int alpha)
{
	this->alpha = alpha;
}

void CGameObject::SetDirection(int nx)
{
	this->nx = nx;
}

void CGameObject::SetState(int state)
{
	this->state = state;
}

bool CGameObject::GetThrought(ObjectTag tag, float nx, float ny)
{
	return false;
}


LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT other)
{
	float sl, st, sr, sb;		// static object bbox -> other
	float ml, mt, mr, mb;		// moving object bbox -> this
	float t, nx, ny;
	DWORD dt = CGame::Instance()->GetDeltaTime();

	other->GetBoundingBox(sl, st, sr, sb);
	this->GetBoundingBox(ml, mt, mr, mb);

	float svx, svy;
	other->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	SweptAABBE(ml, mt, mr, mb, rdx, rdy, sl, st, sr, sb, t, nx, ny);

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, rdx, rdy, other);
	return e;
}

void CGameObject::SweptAABBE(float ml, float mt, float mr, float mb, float rdx, float rdy, float sl, float st, float sr, float sb, float& t, float& nx, float& ny)
{
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

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	if (rdx == 0 && rdy == 0) return;		// moving object is not moving > obvious no collision

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
	else if (rdy < 0)
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


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return; //???

	t = t_entry;


	// decide diretion of collision
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
}

CGameObject::CGameObject()
{
	IsCollisionEnabled = true;
	tag = ObjectTag::None;
	bboxHeight = 0.0f;
	bboxWidth = 0.0f;
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




bool CGameObject::CheckCollision(vector<LPGAMEOBJECT>* coObjects)
{
	if (!IsCollisionEnabled) return false;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->IsCollisionEnabled)
		{
			LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

			if (e != nullptr && e->t > 0 && e->t <= 1.0f) // co va cham
				coEvents.push_back(e);
			else
				delete e;
		}

	}


	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
	
	if (coEvents.size() == 0) return false;

	//DebugOut(L"COLLISIN DETECTED\n");
	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;

	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	//coEventsResult.clear();

	//for (UINT i = 0; i < coEvents.size(); i++)
	//{
	//	LPCOLLISIONEVENT c = coEvents[i];
	//	if (c->ny != -1 && c->obj->GetTag() == ObjectTag::GhostPlatform) continue;

	//	if (c->t < min_tx && c->nx != 0) {
	//		min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
	//	}

	//	if (c->t < min_ty && c->ny != 0) {
	//		min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
	//	}
	//}

	//if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	//if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);

	float sl, st, sr, sb;		// static object bbox -> other
	float ml, mt, mr, mb;		// moving object bbox -> this
	float t, rnx, rny;
	this->GetBoundingBox(ml, mt, mr, mb);

	coEventsResult.clear();
	for each (LPCOLLISIONEVENT c in coEvents)
	{
		for each (LPCOLLISIONEVENT cr in coEventsResult)
		{
			float dx = c->dx;
			float dy = c->dy;
			if (c->nx != 0) {
				dy = dy * cr->t + (c->dy > 0 ? -1 : 1) * 0.002f;
			}
			else {
				dx = dx * cr->t + (c->dx > 0 ? -1 : 1) * 0.002f;
			}
			c->obj->GetBoundingBox(sl, st, sr, sb);
			this->SweptAABBE(ml, mt, mr, mb, dx, dy, sl, st, sr, sb, t, rnx, rny);
			if (t <= 0 || t > 1) {
				c->t = t;
			}
		}
		if (c->t > 0 && c->t <= 1) {
			coEventsResult.push_back(c);
		}
	}

	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT c = coEventsResult[i];
		if (c->obj->GetThrought(tag, c->nx, c->ny)) continue;

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}

	// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
	//if (rdx != 0 && rdx != dx)
		//x += nx * abs(rdx);

	// block every object first!
	x += (min_tx * dx + nx * 0.02f) * CGame::Instance()->GetTimeScale();
	y += (min_ty * dy + ny * 0.02f) * CGame::Instance()->GetTimeScale();

	if (nx != 0) vx = 0;
	if (ny != 0) vy = 0;

	for each (LPCOLLISIONEVENT coEvent in coEventsResult)
	{
		OnCollisionEnter(coEvent);
		//LPCOLLISIONEVENT otherEvent = new CCollisionEvent(coEvent->t, -coEvent->nx, -coEvent->ny, coEvent->dx, coEvent->dy, this);
		//coEvent->obj->OnCollisionEnter(otherEvent);
	}
	
	return true;
}

ObjectTag CGameObject::GetTag()
{
	return tag;
}

void CGameObject::SetTag(ObjectTag tag)
{
	this->tag = tag;
}

void CGameObject::RenderCollisionBox()
{
	auto tex = CLocator<ITexsManager>().Get()->Get(10);
	RECT bbRect;
	bbRect.left = 0;
	bbRect.top = 0;
	bbRect.right = bboxWidth;
	bbRect.bottom = bboxHeight;

	float cx, cy;
	CGame::Instance()->GetCurrentScene()->GetCamPos(cx, cy);
	Vector3 p((int)(x - cx), (int)(y - cy), 0);
	LPD3DXSPRITE spriteHandler = CLocator<IDirectX>().Get()->SpriteHandler();
	spriteHandler->Draw(tex, &bbRect, &Vector3((int)bboxWidth / 2, (int)bboxHeight / 2, 0), &p , D3DCOLOR_ARGB(64, 255, 255, 255));
}

void CGameObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - bboxWidth / 2;
	t = y - bboxHeight / 2;
	r = x + bboxWidth / 2;
	b = y + bboxHeight / 2;
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
	//if (coObjects == NULL) return;
	dx = vx * dt;
	dy = vy * dt;

	if (tag != ObjectTag::Ground && tag != ObjectTag::GhostPlatform)
	{
		if (!CheckCollision(coObjects))
		{
			x += dx * CGame::Instance()->GetTimeScale();
			y += dy * CGame::Instance()->GetTimeScale();
		}
	}
}




CGameObject::~CGameObject()
{
}
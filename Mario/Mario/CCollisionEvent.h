#pragma once
class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

class CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

class CCollisionEvent
{
public:
	LPGAMEOBJECT obj;
	float t, nx, ny;

	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = nullptr);

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b);
};
#include "CCollisionEvent.h"

CCollisionEvent::CCollisionEvent(float t, float nx, float ny, float dx, float dy, LPGAMEOBJECT obj)
{
    this->t = t;
    this->nx = nx;
    this->ny = ny;
    this->dx = dx;
    this->dy = dy;
    this->obj = obj;
}

bool CCollisionEvent::compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
{
    return a->t < b->t;
}

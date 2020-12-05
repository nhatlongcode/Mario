#pragma once
#include "CMario.h"
#include "Tail.h"
class CRaccoonMario : public CMario
{
protected:
    void HandleFall();
    Tail* tail;
    long attackBegin = -1;
    long attackTime = 300;
public:
    CRaccoonMario();
    void HandleAtk();
    void HandleFly(float flyForce);
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
    void RenderCollisionBox();
    void Render();
};


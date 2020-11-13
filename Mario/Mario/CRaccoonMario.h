#pragma once
#include "CMario.h"
class CRaccoonMario :
    public CMario
{
public:
    CRaccoonMario();
    void HandleAtk();
    void HandleFly(float flyForce);
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
protected:
    void HandleFall();
    long attackBegin = -1;
    long attackTime = 300;

};


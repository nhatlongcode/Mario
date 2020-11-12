#pragma once
#include "CMario.h"
class CFireMario :
    public CMario
{
protected:
    void HandleAtk();
public:
    CFireMario();
    long attackBegin = -1;
    long attackTime = 200;
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};


#pragma once
#include "CMario.h"
class CRaccoonMario :
    public CMario
{
public:
    CRaccoonMario();
    void HandleFall();
    void HandleAtk();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

protected:
    long attackBegin = -1;
    long attackTime = 250;

};


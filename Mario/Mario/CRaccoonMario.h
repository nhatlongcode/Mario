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
    long attackStart = -1;

    long marioAttackTime = 250;

};


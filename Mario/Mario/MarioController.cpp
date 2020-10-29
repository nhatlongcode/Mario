#include "MarioController.h"
#include "CSmallMario.h"
#include "CBigMario.h"
#include "CFireMario.h"
#include "CRaccoonMario.h"

void MarioController::Init()
{
    CMario* smallMario = new CSmallMario();
    list[MARIO_TYPE_SMALL] = smallMario;

    CMario* bigMario = new CBigMario();
    list[MARIO_TYPE_SUPER] = bigMario;

    CMario* fireMario = new CFireMario();
    list[MARIO_TYPE_FIRE] = fireMario;

    CMario* raccoonMario = new CRaccoonMario();
    list[MARIO_TYPE_RACCOON] = raccoonMario;

}

CMario* MarioController::GetMario(int id, float posX, float posY)
{
    CMario* mario = list[id];
    mario->SetPosition(posX, posY);
    return mario;
}


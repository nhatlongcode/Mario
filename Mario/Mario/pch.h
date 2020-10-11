#pragma once

#include <d3dx9.h>
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <signal.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

#include "CAnimation.h"
#include "CAnimationFrame.h"
#include "CAnimationsManager.h"
#include "CDebug.h"
#include "CDirectX.h"
#include "CGame.h"
#include "CGameObject.h"
#include "CLocator.h"
#include "CSprite.h"
#include "CSpritesManager.h"
#include "CTexturesManager.h"
#include "CWindow.h"
#include "MarioDefines.h"
#include "Utils.h"

using namespace std;

typedef CAnimationFrame* LPFRAME;
typedef CAnimation* LPANIMATION;
typedef CSprite* LPSPRITE;
typedef CTexturesManager* LPTEXTURES;
typedef LPDIRECT3DTEXTURE9 LPTEXTURE;
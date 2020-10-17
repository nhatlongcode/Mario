#pragma once
#include <d3dx9.h>
// DIRECTX ---------------------------------------------------
typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef LPDIRECT3DTEXTURE9 LPTEXTURE;
#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024

// KEYBOAAAARD ----------------------------------------------------

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024

// WINDOW ----------------------------------------------------

#define WINDOW_CLASS_NAME L"MARIO"
#define MAIN_WINDOW_TITLE L"MARIO BROS 3"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define BRICK_TEXTURE_PATH L"brick.png"

// COLOR -----------------------------------------------------

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

// TEXTURES ----------------------------------------------------

#define PATH_TEX_MARIO L"Textures\\mario2.png"
#define ID_TEX_MARIO "TEX_MARIO"

// MARIO -------------------------------------------------------
#define MARIO_WALKING_SPEED		0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_GRAVITY			0.1f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300


#define MARIO_ANI_IDLE_RIGHT		0
#define MARIO_ANI_IDLE_LEFT			1
#define MARIO_ANI_WALKING_RIGHT		2
#define MARIO_ANI_WALKING_LEFT		3
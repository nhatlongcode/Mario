#pragma once
#include <d3dx9.h>
// DIRECTX ---------------------------------------------------
typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef LPDIRECT3DTEXTURE9 LPTEXTURE;

// KEYBOAAAARD ----------------------------------------------------

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024

// WINDOW ----------------------------------------------------

#define WINDOW_CLASS_NAME L"MARIO"
#define MAIN_WINDOW_TITLE L"MARIO BROS 3"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// COLOR -----------------------------------------------------

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

// SCENE-------------------------------------------------------
#define SCENE_SECTION_UNKNOWN			-1
#define SCENE_SECTION_TEXTURES			2
#define SCENE_SECTION_SPRITES			3
#define SCENE_SECTION_ANIMATIONS		4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS			6

#define MAX_SCENE_LINE 1024

// TEXTURES ----------------------------------------------------

#define TEX_MARIO_ID 0
#define TEX_MARIO_PATH L"Textures\\mario2.png"

// MARIO -------------------------------------------------------
#define MARIO_LEVEL_SMALL 0
#define MARIO_LEVEL_BIG 1

#define MARIO_WALKING_SPEED			0.1f
#define MARIO_JUMP_SPEED_Y			0.105f
#define MARIO_GRAVITY				0.1f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	1
#define MARIO_STATE_WALKING_LEFT	2
#define MARIO_STATE_JUMPING			3
#define MARIO_STATE_RUNNING			4
#define MARIO_STATE_ATACKING		5
#define MARIO_STATE_DIE				6



#define MARIO_TYPE_SMALL			0
#define MARIO_TYPE_SUPER			1
#define MARIO_TYPE_FIRE				2
#define MARIO_TYPE_RACOON			3
#define MARIO_TYPE_HAMMER			4
#define MARIO_TYPE_FROG				5


#define MARIO_ANI_IDLE_RIGHT		0
#define MARIO_ANI_IDLE_LEFT			1
#define MARIO_ANI_WALKING_RIGHT		2
#define MARIO_ANI_WALKING_LEFT		3
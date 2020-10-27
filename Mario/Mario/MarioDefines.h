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

#define MAX_FRAME_RATE 120


// COLOR -----------------------------------------------------

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

// GAME FILE --------------------------------------------------
#define GAME_FILE_SECTION_UNKNOWN		-1
#define GAME_FILE_SECTION_SETTINGS		1
#define GAME_FILE_SECTION_SCENES		2

// SCENE-------------------------------------------------------
#define SCENE_SECTION_UNKNOWN			-1
#define SCENE_SECTION_TEXTURES			2
#define SCENE_SECTION_SPRITES			3
#define SCENE_SECTION_ANIMATIONS		4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS			6

#define MAX_SCENE_LINE	1024
#define MAX_GAME_LINE	1024

// TEXTURES ----------------------------------------------------

#define TEX_MARIO_ID 0
#define TEX_MARIO_PATH L"Textures\\mario2.png"

// DIRECTION ---------------------------------------------------

#define DIRECTION_RIGHT 1
#define DIRECTION_LEFT	-1

// OBJECT TYPE ------------------------------------------------

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3

#define OBJECT_TYPE_PORTAL	50

// MARIO -------------------------------------------------------
#define MARIO_LEVEL_SMALL 0
#define MARIO_LEVEL_BIG 1

#define MARIO_WALKING_SPEED			0.1f
#define MARIO_JUMP_SPEED_Y			0.105f
#define MARIO_GRAVITY				0.1f


#define MARIO_TYPE_SMALL			10000
#define MARIO_TYPE_SUPER			11000
#define MARIO_TYPE_FIRE				12000
#define MARIO_TYPE_RACOON			13000
#define MARIO_TYPE_HAMMER			14000
#define MARIO_TYPE_FROG				15000


#define MARIO_ANI_ICON		0
#define MARIO_ANI_IDLE		1
#define MARIO_ANI_WALK		2
#define MARIO_ANI_SKID		3
#define MARIO_ANI_ATK		4
#define MARIO_ANI_JUMP		5
#define MARIO_ANI_FALL		6
#define MARIO_ANI_RUN		7
#define MARIO_ANI_FLY		8
#define MARIO_ANI_CRUNCH	9
#define MARIO_ANI_SLIDE		10
#define MARIO_ANI_PIPE		11
#define MARIO_ANI_BRING		12
#define MARIO_ANI_KICK		13
#define MARIO_ANI_DIVE		14
#define MARIO_ANI_SWIM		15
#define MARIO_ANI_CLIMB		16


// GOOMBA ---------------------------------------------------
#define GOOMBA_WALKING_SPEED 0.05f;

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1

// BRICK -----------------------------------------------------
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16
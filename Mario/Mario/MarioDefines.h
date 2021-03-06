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
#define WND_WIDTH	735
#define WND_HEIGHT	735
#define GAME_WIDTH	735
#define GAME_HEIGHT	570

#define MAX_FRAME_RATE 120

// FONT -----------------------------------------------------

#define MARIO_FONT_ID 5

// COLOR -----------------------------------------------------

#define BACKGROUND_COLOR D3DCOLOR_XRGB(181, 235, 242)

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
#define SCENE_SECTION_GROUNDS			7
#define SCENE_SECTION_GHOSTPLATFORM		8
#define SCENE_SECTION_UI				9
#define SCENE_SECTION_FONTS				10
#define SCENE_SECTION_MAP				11
#define SCENE_SECTION_PIPE				12

#define MAX_SCENE_LINE	1024
#define MAX_GAME_LINE	1024

// MAP----------------------------------------------------------
#define MAP_SECTION_UNKNOWN	0
#define MAP_SECTION_SIZE	1
#define MAP_SECTION_DATA	2

// CAMERA ------------------------------------------------------
#define CAMERA_OFFSET_TOP	140.0f
#define CAMERA_OFFSET_LEFT	270.0f
#define CAMERA_OFFSET_RIGHT	270.0f
#define CAMERA_OFFSET_BOT	144.0f

#define CAMERA_BORDER_TOP	0.0f
#define CAMERA_BORDER_LEFT	0.0f
#define CAMERA_BORDER_RIGHT	8118.0f
#define CAMERA_BORDER_BOT	1250.0f

// DIRECTION ---------------------------------------------------

#define DIRECTION_RIGHT	1
#define DIRECTION_LEFT	-1

// OBJECT TYPE ------------------------------------------------

#define OBJECT_TYPE_MARIO			0
#define OBJECT_TYPE_QUESTIONBRICK	1
#define OBJECT_TYPE_GOOMBA			2
#define OBJECT_TYPE_KOOPAS			3
#define OBJECT_TYPE_BREAKABLEBRIK	4
#define OBJECT_TYPE_FLYGOOMBA		5
#define OBJECT_TYPE_FLYKOOPAS		6
#define OBJECT_TYPE_VENUS			7
#define OBJECT_TYPE_PIRANHA			8
#define OBJECT_TYPE_SHROOM			9
#define OBJECT_TYPE_LEAF			10
#define OBJECT_TYPE_PBUTTON			11
#define OBJECT_TYPE_PIPE			12

#define OBJECT_TYPE_PORTAL	50

// MARIO -------------------------------------------------------
#define MARIO_SMALL_BBOX_WIDTH		36
#define MARIO_SMALL_BBOX_HEIGHT		45

#define MARIO_BIG_BBOX_WIDTH			42
#define MARIO_BIG_BBOX_HEIGHT			81
#define MARIO_BIG_CRUNCH_BBOX_HEIGHT	45

#define MARIO_RUN_DRAG_FORCE	0.0004f
#define MARIO_WALK_DRAG_FORCE	0.0005f

#define MARIO_WALKING_SPEED			0.23f
#define MARIO_RUNNING_SPEED			0.6f
#define MARIO_ACCELERATION			0.0005f
#define MARIO_IDLE_SPEED			0.0f
#define MARIO_MAX_RUN				0.7f
#define MARIO_MAX_WALK				0.2f

#define MARIO_JUMP_SHORT_SPEED		-0.8f
#define MARIO_JUMP_HIGH_SPEED		-0.5f
#define MARIO_JUMP_MAX				10.0f

#define MARIO_FLY_HIGH_FORCE		-0.5f
#define MARIO_FLY_SHORT_FORCE		-0.3f
#define MARIO_FLY_MAX				15.0f

#define MARIO_MAX_JUMP				15.0f
#define MARIO_GRAVITY				0.05f
#define MARIO_FALL_RACCOON			0.1f


#define MARIO_TYPE_SMALL			10000
#define MARIO_TYPE_SUPER			11000
#define MARIO_TYPE_FIRE				12000
#define MARIO_TYPE_RACCOON			13000
#define MARIO_TYPE_HAMMER			14000
#define MARIO_TYPE_FROG				15000


#define MARIO_STATE_ICON		0
#define MARIO_STATE_IDLE		1
#define MARIO_STATE_WALK		2
#define MARIO_STATE_SKID		3
#define MARIO_STATE_ATK			4
#define MARIO_STATE_JUMP		5
#define MARIO_STATE_FALL		6
#define MARIO_STATE_RUN			7
#define MARIO_STATE_FLY			8
#define MARIO_STATE_CRUNCH		9
#define MARIO_STATE_SLIDE		10
#define MARIO_STATE_DIE			11
#define MARIO_STATE_PIPE		11
#define MARIO_STATE_BRING		12
#define MARIO_STATE_KICK		13
#define MARIO_STATE_DIVE		14
#define MARIO_STATE_FLY_ATK		15
#define MARIO_STATE_CLIMB		16

// FIRE BALL ------------------------------------------------
#define FIREBALL_ANIMSET	30000
#define FIREBALL_BBOX_WIDTH		24
#define FIREBALL_BBOX_HEIGHT	24

#define FIREBALL_SPEED_X	0.5f

#define FIREBALL_STATE_FLY		0
#define FIREBALL_STATE_EXPLO	1




// GOOMBA ---------------------------------------------------
#define GOOMBA_ANIMSET	20000

#define GOOMBA_WALKING_SPEED 0.05f;

#define GOOMBA_BBOX_WIDTH		35
#define GOOMBA_BBOX_HEIGHT		35
#define GOOMBA_BBOX_HEIGHT_DIE	27

#define GOOMBA_STATE_WALKING		0
#define GOOMBA_STATE_DIE			1
#define GOOMBA_STATE_DIE_INSTANT	2


// KOOPAS ----------------------------------------------------
#define KOOPAS_ANIMSET	21000

#define KOOPAS_SPEED_WALK	0.05f;
#define KOOPAS_SPEED_SPIN	0.5f;

#define KOOPAS_BBOX_WIDTH	48
#define KOOPAS_BBOX_HEIGHT	78

#define KOOPAS_SHELL_BBOX_WIDTH		35
#define KOOPAS_SHELL_BBOX_HEIGHT	35

#define KOOPAS_STATE_WALK		0
#define KOOPAS_STATE_SHELL		1
#define KOOPAS_STATE_SPIN		2
#define KOOPAS_STATE_DIE		3

// BRICK -----------------------------------------------------
#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48

#define GHOST_BBOX_WIDTH	100
#define GHOST_BBOX_HEIGHT	100
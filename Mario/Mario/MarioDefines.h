#pragma once
#include <d3dx9.h>
// DIRECTX ---------------------------------------------------

typedef LPDIRECT3DTEXTURE9 LPTEXTURE;
#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024

// WINDOW ----------------------------------------------------

#define WINDOW_CLASS_NAME L"MARIO"
#define MAIN_WINDOW_TITLE L"MARIO BROS 3"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BRICK_TEXTURE_PATH L"brick.png"

// COLOR -----------------------------------------------------

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

// TEXTURES ----------------------------------------------------

#define PATH_TEX_MARIO L"Textures\\mario.png"
#define ID_TEX_MARIO "TEX_MARIO"

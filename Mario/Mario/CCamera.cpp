#include "CCamera.h"
#include "CGame.h"
#include "CMario.h"

CCamera::CCamera(int width, int height)
{
	this->width = width;
	this->height = height;
}

void CCamera::SetOffSet(float offLeft, float offRight, float offTop, float offBot)
{
	this->offSetTop = offTop;
	this->offSetBot = offBot;
	this->offSetLeft = offLeft;
	this->offSetRight = offRight;
}

void CCamera::SetBorder(float left, float right, float top, float bot)
{
	this->borderLeft = left;
	this->borderRight = right;
	this->borderTop = top;
	this->borderBot = bot;
}

void CCamera::GetCamPos(float& cx, float& cy)
{
	cx = this->posX;
	cy = this->posY;
}

void CCamera::SetCamPos(float cx, float cy)
{
	this->posX = cx;
	this->posY = cy;
}

void CCamera::SetPlayer(CMario* mario)
{
	this->player = mario;
}

void CCamera::Update()
{
	if (player == NULL) return;
	float px, py;
	player->GetPosition(px, py);

	if (px > posX + width - offSetRight)
	{
		posX = px - width + offSetRight;
	}
	else if (px < posX + offSetLeft)
	{
		posX = px - offSetLeft;
	}

	if (py > posY + height - offSetBot)
	{
		posY = py - height + offSetBot;
	}
	else if (py < posY + offSetTop)
	{
		posY = py - offSetTop;
	}

	if (borderLeft != -1)
	{
		if (posX < borderLeft) posX = borderLeft;
	}

	if (borderTop != -1)
	{
		if (posY < borderTop) posY = borderTop;
	}

	if (borderRight != -1)
	{
		if (posX + width > borderRight) posX = borderRight - width;
	}

	if (borderBot != -1)
	{
		if (posY + height > borderBot) posY = borderRight - height;
	}
}

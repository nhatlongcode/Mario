#include "CPipe.h"
#include "CGame.h"

CPipe::CPipe()
{
	SetBoundingBox(96, 96);
	SetTag(ObjectTag::Pipe);
	IsCollisionEnabled = true;
	pipeInX = pipeInY = pipeOutX = pipeOutY = 0.0f;
	this->x = this->y = 0.0f;
	offSetTop = offSetBot = offSetLeft = offSetRight = 0.0f;
	borderTop = borderBot = borderLeft = borderRight = 0.0f;
}

void CPipe::GoToPipe()
{
	CCamera* cam = CGame::Instance()->GetCurrentScene()->GetCamera();

	cam->SetBorder(borderLeft, borderRight, borderTop, borderBot);
	cam->SetOffSet(offSetLeft, offSetRight, offSetTop, offSetBot);

	CGame::Instance()->GetCurrentScene()->GetPlayer()->SetPosition(pipeOutX, pipeOutY);
}

void CPipe::SetSprite(LPSPRITE spriteIn, LPSPRITE spriteOut)
{
	this->spriteIn = spriteIn;
	this->spriteOut = spriteOut;
}

void CPipe::SetType(PipeType type)
{
	pipeType = type;
}

void CPipe::SetCameraPos(float posInX, float posInY, float posOutX, float posOutY)
{
	pipeInX = posInX;
	pipeInY = posInY;
	pipeOutX = posOutX;
	pipeOutY = posOutY;
	this->x = posInX;
	this->y = posInY;
}


void CPipe::SetOffSet(float offSetTop, float offSetBot, float offSetLeft, float offSetRight)
{
	this->offSetTop = offSetTop;
	this->offSetBot = offSetBot;
	this->offSetLeft = offSetLeft;
	this->offSetRight = offSetRight;
}

void CPipe::SetBorder(float borderTop, float borderBot, float borderLeft, float borderRight)
{
	this->borderTop = borderTop;
	this->borderBot = borderBot;
	this->borderLeft = borderLeft;
	this->borderRight = borderRight;
}

PipeType CPipe::GetPipeType()
{
	return pipeType;
}

void CPipe::Render()
{
	spriteIn->Draw(pipeInX, pipeInY);
	spriteOut->Draw(pipeOutX, pipeOutY);
}

void CPipe::SetState(int state)
{
	if (state == 1) GoToPipe();
}

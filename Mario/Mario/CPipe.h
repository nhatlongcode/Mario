#include "CGameObject.h"


class CPipe : public CGameObject
{
private:
	float pipeInX, pipeInY, pipeOutX, pipeOutY;
	float offSetTop, offSetBot, offSetLeft, offSetRight, borderTop, borderBot, borderLeft, borderRight;
	LPSPRITE spriteOut;
	LPSPRITE spriteIn;
	PipeType pipeType;
public:
	CPipe();
	void GoToPipe();
	void SetSprite(LPSPRITE spriteIn, LPSPRITE spriteOut);
	void SetType(PipeType type);
	void SetCameraPos(float posInX, float posInY, float posOutX, float posOutY);
	void SetOffSet(float offSetTop, float offSetBot, float offSetLeft, float offSetRight);
	void SetBorder(float borderTop, float borderBot, float borderLeft, float borderRight);
	PipeType GetPipeType();
	virtual void Render() override;
	virtual void SetState(int state) override;
};
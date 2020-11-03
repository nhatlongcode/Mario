#pragma once

class CMario;

class CCamera
{
private:
	int width;
	int height;

	float posX;
	float posY;
	float offSetTop;
	float offSetBot;
	float offSetRight;
	float offSetLeft;

	float borderLeft = -1;
	float borderRight = -1;
	float borderTop = -1;
	float borderBot = -1;

	CMario* player;
public:
	CCamera(int width, int height);
	void SetOffSet(float offLeft, float offRight, float offTop, float offBot);
	void SetBorder(float left, float right, float top, float bot);
	void GetCamPos(float& cx, float& cy);
	void SetCamPos(float cx, float cy);
	void SetPlayer(CMario* mario);
	void Update();
};
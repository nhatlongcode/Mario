#pragma once
#include "CUIElement.h"
#include "CImage.h"
#include "CText.h"

class CGamePanel : public CUIElement
{
private:
	CImage *botFrame, *blackArrow, *whiteArrow, *blackP, *whiteP;
	CText  *worldIndexText, *moneyText,*timeText, *scoreText, *lifeText;
public:
	CGamePanel();
	void SetFrame(float x, float y, int left, int top, int width, int height, float scaleX, float scaleY, int texID);
	void SetBlackArrow(int left, int top, int width, int height, float scaleX, float scaleY, int texID);
	void SetWhiteArrow(int left, int top, int width, int height, float scaleX, float scaleY, int texID);
	void SetBlackP(int left, int top, int width, int height, float scaleX, float scaleY, int texID);
	void SetWhiteP(int left, int top, int width, int height, float scaleX, float scaleY, int texID);

	void SetIndexText(int index);
	void SetMoney(int money);
	void SetTime(int time);
	void SetScore(int score);
	void SetLife(int life);

	void Render() override;
};

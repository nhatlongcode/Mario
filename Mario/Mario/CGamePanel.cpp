#include "CGamePanel.h"
#include "CLocator.h"
#include "ITexsManager.h"
#include <string>

CGamePanel::CGamePanel()
{
	timeText = new CText("000", MARIO_FONT_ID);
	moneyText = new CText("000", MARIO_FONT_ID);
	worldIndexText = new CText("000", MARIO_FONT_ID);
	scoreText = new CText("000", MARIO_FONT_ID);
	lifeText = new CText("000", MARIO_FONT_ID);
	
	timeText->SetSize(0.9f);
	moneyText->SetSize(0.9f);
	worldIndexText->SetSize(0.9f);
	scoreText->SetSize(0.9f);
	lifeText->SetSize(0.9f);

	timeText->SetPosition(391.0f, 633.0f);
	moneyText->SetPosition(0.0f, 633.0f);
	worldIndexText->SetPosition(0.0f, 633.0f);
	scoreText->SetPosition(0.0f, 633.0f);
	lifeText->SetPosition(0.0f, 633.0f);
}

void CGamePanel::SetFrame(float x, float y, int left, int top, int width, int height, float scaleX, float scaleY, int texID)
{
	auto tex = CLocator<ITexsManager>().Get()->Get(texID);
	botFrame = new CImage(left, top, width, height, scaleX, scaleY, tex);
	botFrame->SetPosition(x, y);
}

void CGamePanel::SetBlackArrow(int left, int top, int width, int height, float scaleX, float scaleY, int texID)
{
	auto tex = CLocator<ITexsManager>().Get()->Get(texID);
	blackArrow = new CImage(left, top, width, height, scaleX, scaleY, tex);
}

void CGamePanel::SetWhiteArrow(int left, int top, int width, int height, float scaleX, float scaleY, int texID)
{
	auto tex = CLocator<ITexsManager>().Get()->Get(texID);
	whiteArrow = new CImage(left, top, width, height, scaleX, scaleY, tex);
}

void CGamePanel::SetBlackP(int left, int top, int width, int height, float scaleX, float scaleY, int texID)
{
	auto tex = CLocator<ITexsManager>().Get()->Get(texID);
	blackP = new CImage(left, top, width, height, scaleX, scaleY, tex);
}

void CGamePanel::SetWhiteP(int left, int top, int width, int height, float scaleX, float scaleY, int texID)
{
	auto tex = CLocator<ITexsManager>().Get()->Get(texID);
	whiteP = new CImage(left, top, width, height, scaleX, scaleY, tex);
}

void CGamePanel::SetIndexText(int index)
{
	worldIndexText->SetContent(std::to_string(index));
}

void CGamePanel::SetMoney(int money)
{
	moneyText->SetContent(std::to_string(money));
}

void CGamePanel::SetTime(int time)
{
	timeText->SetContent(std::to_string(time));
}

void CGamePanel::SetScore(int score)
{
	scoreText->SetContent(std::to_string(score));
}

void CGamePanel::SetLife(int life)
{
	lifeText->SetContent(std::to_string(life));
}

void CGamePanel::Render()
{
	botFrame->Render();
	worldIndexText->Render();
	moneyText->Render();
	timeText->Render();
	scoreText->Render();
	lifeText->Render();
}

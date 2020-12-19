#include "CUIElement.h"

void CUIElement::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CUIElement::GetPosition(float& x, float& y)
{
	x = this->x;
	y = this->y;
}

void CUIElement::GetAlpha(int& alpha)
{
	alpha = this->alpha;
}

void CUIElement::SetAlpha(int alpha)
{
	this->alpha = alpha;
}

void CUIElement::Render()
{
	// render rong;
}

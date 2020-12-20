#pragma once
#include "CUIElement.h"
#include <string.h>
#include <vector>
#include "CChar.h"
class CText : public CUIElement
{
private:
	float distance = 0.0f;
	int fontID;
	float size = 1.0f;
	std::string content;
	std::vector<CChar*> listChar;
public:
	CText(std::string content = "", int fontID = MARIO_FONT_ID);
	void ResetString();
	void Render() override;
	void SetPosition(float x, float y) override;
	void SetSize(float size);
	void SetContent(std::string content);
	void SetDistance(float distance);
};
#pragma once
#include "CUIElement.h"
#include <string.h>
#include <vector>
#include "CChar.h"
class CText : public CUIElement
{
private:
	float distance = 0.0f;
	int fontID, size = 1;
	std::string content;
	std::vector<CChar*> listChar;
public:
	void ResetString();
	void Render() override;
	void SetContent(std::string content);
};
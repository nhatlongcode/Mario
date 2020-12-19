#include "CText.h"
#include "Utils.h"
#include "CLocator.h"
#include "CFontManager.h"
#include <iostream>
#include <cstring>

using namespace std;

CText::CText(std::string content, int fontID)
{
	this->content = content;
	this->fontID = fontID;
	size = 1;
	distance = 0.0f;
	alpha = 255;
	ResetString();
}

void CText::ResetString()
{
	float posX = x; //relative

	for (int i = 0; i < listChar.size(); i++)
	{
		delete listChar[i];
	}
	listChar.clear();

	if (content.size() == 0) return;

	for (int i = 0; i < content.size(); i++)
	{
		char c = content[i];
		CChar* cc = CLocator<IFontManager>().Get()->GetFont(fontID, (int)c)->GetChar(size, size);
		cc->SetAlpha(this->alpha);
		if (i == 0)
		{
			cc->SetPosition(posX, this->y);
		}
		else
		{
			posX += float(listChar[i - 1]->GetWidth()) + distance;
			cc->SetPosition(posX, y);
		}
		listChar.push_back(cc); //turn fontInfo to char and add to vector
	}
}

void CText::Render()
{
	for (int i = 0; i < listChar.size(); i++)
	{
		listChar[i]->Render();
	}
}

void CText::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	ResetString();
}

void CText::SetContent(std::string content)
{
	this->content = content;
	ResetString();
}

void CText::SetDistance(float distance)
{
	this->distance = distance;
}

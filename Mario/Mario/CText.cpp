#include "CText.h"
#include "CLocator.h"
#include "CFontManager.h"

void CText::ResetString()
{
	float posX = x; //relative
	for (int i = 0; i < listChar.size(); i++)
	{
		delete listChar[i];
	}
	listChar.clear();

	if (content == "") return;

	for (int i = 0; i < content.size(); i++)
	{
		char c = content[i];
		CChar* cc = CLocator<IFontManager>().Get()->GetFont(fontID, (int)c).GetChar(size, size);
		if (i == 0)
		{
			cc->SetPosition(this->x, this->y);
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

void CText::SetContent(std::string content)
{
	this->content = content;
	ResetString();
}

#include "CCanvas.h"
#include "Utils.h"
CCanvas::CCanvas()
{
}

CCanvas::~CCanvas()
{
	for (int i = 0; i < listUI.size(); i++)
	{
		delete listUI.at(i);
	}
}

void CCanvas::Update(DWORD dt)
{
	if (listUI.size() == 0)
	{
		DebugOut(L"empty canvas\n");
	}
}

void CCanvas::Add(LPUI ui)
{
	listUI.push_back(ui);
}

void CCanvas::Render()
{
	for (int i = 0; i < listUI.size(); i++)
	{
		auto ui = listUI.at(i);
		if (ui->isEnabled) ui->Render();
	}
}

void CCanvas::Clear()
{
	listUI.clear();
}

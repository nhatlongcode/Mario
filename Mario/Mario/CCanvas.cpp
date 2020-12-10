#include "CCanvas.h"

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
		if (ui->IsEnable) ui->Render();
	}
}

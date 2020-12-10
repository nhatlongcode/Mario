#pragma once
#include "CUIElement.h"
#include <vector>

class CCanvas
{
private:
	std::vector<LPUI> listUI;
public:
	CCanvas();
	~CCanvas();
	void Update(DWORD dt);
	void Add(LPUI ui);
	void Render();
};
typedef CCanvas* LPCANVAS;
#pragma once
#include <d3dx9.h>
#include <unordered_map>
#include "CLocator.h"
#include "CDirectX.h"

class CUIElement
{
protected:
	float x, y;
	int id, alpha;
public:
	bool isEnabled = true;
	
	virtual void SetPosition(float x, float y);
	void GetPosition(float& x, float& y);

	void GetAlpha(int& alpha);
	void SetAlpha(int alpha);

	virtual void Render();
};

typedef CUIElement* LPUI;
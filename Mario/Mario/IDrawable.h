#pragma once
class IDrawable
{
public:
	bool isEnable = false;
	virtual void Render(float, float) = 0;
};
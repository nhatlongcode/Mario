#pragma once

class CFont
{
private:
	int l, t, w, h;
	int textID;
public:
	CFont(int left, int top, int width, int height, int textID);
	void Render(float x, float y);
};
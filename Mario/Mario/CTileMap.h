#pragma once
class CTileMap
{
private:
	int x;
	int y;
	int alpha;
	int spriteID;
public:
	CTileMap(int x, int y, int spriteID);
	void SetAlpha(int alpha);
	void Render();
};
#pragma once
class CTileMap
{
private:
	int x;
	int y;
	int spriteID;
public:
	CTileMap(int x, int y, int spriteID);
	void Render();
};
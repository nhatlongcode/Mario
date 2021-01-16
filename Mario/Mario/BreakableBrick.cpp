#include "BreakableBrick.h"

BreakableBrick::BreakableBrick()
{
	SetBoundingBox(48, 48);
	SetAnimationSet(30005);
	IsCollisionEnabled = true;
	pButton = false;
	isBreaked = false;
	SetState(0);

	BrickPiece* piece = new BrickPiece();
	piece->SetPosition(this->x, this->y);
	piece->SetSprite(30014);
	pieces.push_back(piece);

	BrickPiece* piece1 = new BrickPiece();
	piece->SetPosition(this->x, this->y);
	piece->SetSprite(30015);
	pieces.push_back(piece1);

	BrickPiece* piece2 = new BrickPiece();
	piece->SetPosition(this->x, this->y);
	piece->SetSprite(30016);
	pieces.push_back(piece2);

	BrickPiece* piece3 = new BrickPiece();
	piece->SetPosition(this->x, this->y);
	piece->SetSprite(30017);
	pieces.push_back(piece3);

}

void BreakableBrick::Render()
{
	if (state == -1) return;
	animSet->at(state)->Render(this->x, this->y);
}

void BreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void BreakableBrick::SetState(int state)
{
	this->state = state;
	if (state == -1) Break();
}

void BreakableBrick::OnCollisionEnter(LPCOLLISIONEVENT other)
{
}

void BreakableBrick::Break()
{
	if (isBreaked) return;
	IsCollisionEnabled = false;
	isBreaked = true;
	
}

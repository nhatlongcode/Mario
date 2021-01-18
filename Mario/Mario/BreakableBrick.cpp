#include "BreakableBrick.h"

BreakableBrick::BreakableBrick()
{
	SetBoundingBox(48, 48);
	SetAnimationSet(30005);
	SetTag(ObjectTag::BreakableBrick);
	IsCollisionEnabled = true;
	pButton = false;
	isBreaked = false;
	SetState(0);

	BrickPiece* piece = new BrickPiece();
	piece->SetPosition(this->x, this->y);
	piece->SetSprite(30014);
	piece->SetBounceBreak(0.3f, -0.5f, 1);
	pieces.push_back(piece);

	BrickPiece* piece1 = new BrickPiece();
	piece1->SetPosition(this->x, this->y);
	piece1->SetSprite(30015);
	piece1->SetBounceBreak(0.3f, -0.5f, -1);
	pieces.push_back(piece1);

	BrickPiece* piece2 = new BrickPiece();
	piece2->SetPosition(this->x, this->y);
	piece2->SetBounceBreak(0.3f, -0.7f, 1);
	piece2->SetSprite(30016);
	pieces.push_back(piece2);

	BrickPiece* piece3 = new BrickPiece();
	piece3->SetPosition(this->x, this->y);
	piece3->SetSprite(30017);
	piece3->SetBounceBreak(0.3f, -0.7f, -1);
	pieces.push_back(piece3);

}

void BreakableBrick::Render()
{
	if (state != -1)
	{
		animSet->at(state)->Render(this->x, this->y);
	}
	if (isBreaked)
	{
		for each (auto piece in pieces)
		{
			piece->Render();
		}
	}
}

void BreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isBreaked)
	{
		for each (auto piece in pieces)
		{
			piece->Update(dt, coObjects);
		}
	}
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
	SetBoundingBox(0, 0);
	for each (auto piece in pieces)
	{
		piece->Break();
	}
	isBreaked = true;
	
}

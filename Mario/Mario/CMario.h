#pragma once
#include "CGameObject.h"
class CMario : public CGameObject
{
protected:
	int level;
	bool isGrounded;
	bool isJumping;
	bool isFalling;
	bool isRunning;
	bool isHighJump;
	bool isFinishHighJump;

	float startX;			// initial position of Mario at scene
	float startY;
	float force;
public:
	CMario();
	void SetState(int state);
	void SetLevel(int level);
	//void BasicActionHandle();

	virtual void Init();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	virtual void HandleMovement();
	virtual void HandleJump();

	void ShortJump();
	void Idle();
	void Walk(int direction);
	//virtual void AttackAction() = 0;
	//virtual void CrunchAction() = 0;

	void Reset();
};


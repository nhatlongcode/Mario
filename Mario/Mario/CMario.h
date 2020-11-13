#pragma once
#include "CGameObject.h"
class CMario : public CGameObject
{
protected:
	int level;
	bool isGrounded;
	bool isAttacking;
	bool isMaxSpeed;
	bool isFlying;
	bool canHighFly;
	bool canHighJump;

	
	float ax;
	float startX;			// initial position of Mario at scene
	float startY;
	float forceJump;
	float forceFly;
	float currentSpeedX;
	float animSpeed;
	DWORD dt;

	void StandingOnGround();
	virtual void HandleMovement();
	virtual void HandleChangeDirection(int direction);
	virtual void HandleFly(float flyForce);
	virtual void HandleFall();
	virtual void HandleAtk();
	void HandleJump(float jumpForce);
	void HandleWalk();
	void HandleRun();
	void HandleSlowDown();
	virtual void HandleInput();
public:
	CMario();
	void SetState(int state);
	void SetLevel(int level);

	virtual void Init();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);


	virtual void OnCollisionEnter(LPCOLLISIONEVENT other);
	//virtual void AttackAction() = 0;
	//virtual void CrunchAction() = 0;

	void Reset();
};


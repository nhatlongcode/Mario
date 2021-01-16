#pragma once
enum class ObjectTag
{
	None,
	Buff,
	GhostPlatform,
	Solid,
	QuestionBrick,
	Brick,
	BreakableBrick,
	Player,
	Koopas,
	Pipe,
	Ground,
	Goomba,
	GoombaFly,
	KoopasFly,
	FireFromMario,
	FireFromEnemy,
};

enum class BrickObjectTag
{
	Buff,
	Coin,
};

enum class PipeType
{
	GoDown,
	GoUp,
};
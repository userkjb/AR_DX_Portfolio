#pragma once

enum class ERenderOrder
{
	BackGroundImage,
	Map,
	MapCol,
	Weapon_Prev,
	StageDoor,
	Player,
	Weapon_Next,
	Boss,
	BossSkill,
	Weapon_FX,
	MapObject,
};


enum class ECollisionOrder
{
	Player,
	Monster,
	WeaponFX,
};

enum class EPlayerState
{
	Idle,
	Run,
	Jump,
	Jumping,
	Dash,
	Die,
};
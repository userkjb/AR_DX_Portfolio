#pragma once

enum class ERenderOrder
{
	BackGroundImage,
	BossSubObject,
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
	Mouse,
};


enum class ECollisionOrder
{
	Player,
	Monster,
	Boss,
	WeaponFX,
	NextMap,
	BossStageStart,
	MapDoor,
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
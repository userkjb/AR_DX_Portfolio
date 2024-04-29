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
	BossBodyFX,
	BossSkill_B,
	BossSkill_F,
	Weapon_FX,
	MapObject,
	Mouse,
};


enum class ECollisionOrder
{
	Player,
	Monster,
	Boss,
	BossSkill,
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
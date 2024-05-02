#pragma once

enum class EObjectOrder
{
	Player,
	Monster,
};

enum class ERenderOrder
{
	BackGroundImage,
	BossSubObject,
	MapBack,
	Map,
	MapCol,
	Weapon_Prev,
	StageDoor,
	Player,
	Weapon_Next,
	Enemy,
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
	Monster_Attack,
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
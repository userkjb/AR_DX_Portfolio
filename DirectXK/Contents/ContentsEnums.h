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
	StageDoor,
	Weapon_Prev,
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
	Monster_Search,
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
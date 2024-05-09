#pragma once
#include <EngineCore/Widget.h>

class UImage;
class ULasleyUI : public UWidget
{
	GENERATED_BODY(UWidget)
public:
	// constrcuter destructer
	ULasleyUI();
	~ULasleyUI();

	// delete Function
	ULasleyUI(const ULasleyUI& _Other) = delete;
	ULasleyUI(ULasleyUI&& _Other) noexcept = delete;
	ULasleyUI& operator=(const ULasleyUI& _Other) = delete;
	ULasleyUI& operator=(ULasleyUI&& _Other) noexcept = delete;

	inline void RecvHit(bool _Val, int _LasleyMaxHp, int _Damage)
	{
		InHit = _Val;
		LasleyMaxHp = _LasleyMaxHp;
		GetWeaponDamage = _Damage;
	}

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

private :
	UImage* HpBar_Back = nullptr;
	UImage* HpBar_Base = nullptr;
	UImage* HpBar_Icon = nullptr;

	bool InHit = false;
	int LasleyMaxHp = 0;
	int GetWeaponDamage = 0;
};


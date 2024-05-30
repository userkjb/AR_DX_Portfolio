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

	inline void RecvHit(bool _Val, float _Percent)
	{
		InHit = _Val;
		GetPercent = _Percent;
	}

	inline void ResetHp(bool _Val)
	{
		ReSet = _Val;
	}

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

private :
	UImage* HpBar_Back = nullptr;
	UImage* HpBar_Base = nullptr;
	UImage* HpBar_HpBar = nullptr;
	UImage* HpBar_Icon = nullptr;

	bool InHit = false;
	bool ReSet = false;
	float GetPercent = 0.0f;
	float HpMax = 0.0f;
};


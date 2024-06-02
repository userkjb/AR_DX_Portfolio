#pragma once
#include <EngineCore/Widget.h>

// 설명 :
class UImage;
class MyWidget : public UWidget
{
	GENERATED_BODY(UWidget)
public:
	// constrcuter destructer
	MyWidget();
	~MyWidget();

	// delete Function
	MyWidget(const MyWidget& _Other) = delete;
	MyWidget(MyWidget&& _Other) noexcept = delete;
	MyWidget& operator=(const MyWidget& _Other) = delete;
	MyWidget& operator=(MyWidget&& _Other) noexcept = delete;

	inline void RecvDamageValue(bool _Boolean, float _Value)
	{
		InDamage = _Boolean;
		InDamagePercent = _Value;
	}

	/// <summary>
	/// 알파값 조절 함수.
	/// </summary>
	/// <param name="_Value"></param>
	inline void RecvHitValue(bool _Value)
	{
		InHit = _Value;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void CreateHpBar();
	void CreateDashBar();
	void CreateDashBar_v2();
	void UpdateDashBar(float _DeltaTime);
	void HpBarUpdate(float _DeltaTime);

	UImage* HpBar_Base = nullptr;
	UImage* HpBar_Ani = nullptr;
	UImage* Hit = nullptr;

	bool InDamage = false;
	bool InHit = false;
	bool IsCreate = false;
	float InDamagePercent = 0.0f;
	//FVector DefaultScale = FVector::Zero;
	float HpBarMax = 0.0f;
	float DashCountTime = 0.0f;

	std::vector<std::pair<UImage*, UImage*>> Dash_Base_Images;
	//std::vector<UImage*> DashBar_Bases;
	//std::vector<UImage*> DashBar_Counts;
	float HitAlpha = 1.0f;
};


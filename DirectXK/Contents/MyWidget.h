#pragma once
#include <EngineCore/Widget.h>

// ���� :
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

	inline std::vector<std::pair<UImage*, UImage*>> GetDashBaseImageV()
	{
		return Dash_Base_Images;
	}

	inline void RecvDamageValue(bool _Boolean, float _Value)
	{
		InDamage = _Boolean;
		Damage = _Value;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void CreateHpBar();
	void CreateDashBar();
	void CreateDashBar_v2();

	UImage* HpBar_Base = nullptr;
	UImage* HpBar_Ani = nullptr;

	bool InDamage = false;
	float Damage = 0.0f;
	FVector DefaultScale = FVector::Zero;
	float DashCountTime = 0.0f;

	std::vector<std::pair<UImage*, UImage*>> Dash_Base_Images;
	std::vector<UImage*> DashBar_Bases;
	std::vector<UImage*> DashBar_Counts;
};


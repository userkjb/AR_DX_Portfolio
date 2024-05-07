#pragma once
#include <EngineCore/Widget.h>

// Ό³Έν :
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

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

private:
	void CalDashCount(float _DeltaTime);

	UImage* HpBar_Base = nullptr;
	UImage* HpBar_Ani = nullptr;

	std::vector<std::pair<UImage*, UImage*>> Dash_Base_Images;

	FVector DefaultScale = FVector::Zero;
	float DashCountTime = 0.0f;
};


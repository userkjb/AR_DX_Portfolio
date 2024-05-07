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

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

private:
	UImage* HpBar_Base = nullptr;
	UImage* HpBar_Ani = nullptr;
	UImage* Dash_Base = nullptr;
	FVector DefaultScale = FVector::Zero;
};


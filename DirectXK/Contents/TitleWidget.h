#pragma once
#include <EngineCore/Widget.h>

class UImage;
class UTitleWidget : public UWidget
{
	GENERATED_BODY(UWidget)
public:
	// constrcuter destructer
	UTitleWidget();
	~UTitleWidget();

	// delete Function
	UTitleWidget(const UTitleWidget& _Other) = delete;
	UTitleWidget(UTitleWidget&& _Other) noexcept = delete;
	UTitleWidget& operator=(const UTitleWidget& _Other) = delete;
	UTitleWidget& operator=(UTitleWidget&& _Other) noexcept = delete;

protected:
	void BeginPlay();
	void Tick(float _DeltaTime) override;

private :
	UImage* GameStart_F = nullptr;
	UImage* GameStart_E = nullptr;
};


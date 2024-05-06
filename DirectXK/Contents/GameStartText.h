#pragma once
#include <Enginecore/Actor.h>

class UTitleWidget;
class AGameStartText : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AGameStartText();
	~AGameStartText();

	// delete Function
	AGameStartText(const AGameStartText& _Other) = delete;
	AGameStartText(AGameStartText&& _Other) noexcept = delete;
	AGameStartText& operator=(const AGameStartText& _Other) = delete;
	AGameStartText& operator=(AGameStartText&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	UTitleWidget* Widget = nullptr;
};


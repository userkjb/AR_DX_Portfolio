#pragma once
#include <EngineCore/Actor.h>

class AWyvern : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AWyvern();
	~AWyvern();

	// delete Function
	AWyvern(const AWyvern& _Other) = delete;
	AWyvern(AWyvern&& _Other) noexcept = delete;
	AWyvern& operator=(const AWyvern& _Other) = delete;
	AWyvern& operator=(AWyvern&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};


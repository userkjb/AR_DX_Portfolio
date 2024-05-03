#pragma once
#include <EngineCore/Actor.h>

// ���� :
class URenderer;
class ATestActor : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ATestActor();
	~ATestActor();

	// delete Function
	ATestActor(const ATestActor& _Other) = delete;
	ATestActor(ATestActor&& _Other) noexcept = delete;
	ATestActor& operator=(const ATestActor& _Other) = delete;
	ATestActor& operator=(ATestActor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void DebugMessageFunction(float _DeltaTime);

	URenderer* Renderer;
	float4 Color;
};


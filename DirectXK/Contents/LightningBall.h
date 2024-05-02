#pragma once
#include <EngineCore/Actor.h>

class ALightningBall : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ALightningBall();
	~ALightningBall();

	// delete Function
	ALightningBall(const ALightningBall& _Other) = delete;
	ALightningBall(ALightningBall&& _Other) noexcept = delete;
	ALightningBall& operator=(const ALightningBall& _Other) = delete;
	ALightningBall& operator=(ALightningBall&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :

};


#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class UDefaultSceneComponent;
class ATentacle : public AActor
{
	GENERATED_BODY(AActor)

public :
	// constrcuter destructer
	ATentacle();
	~ATentacle();

	// delete Function
	ATentacle(const ATentacle& _Other) = delete;
	ATentacle(ATentacle&& _Other) noexcept = delete;
	ATentacle& operator=(const ATentacle& _Other) = delete;
	ATentacle& operator=(ATentacle&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void StateInit();

	void StartBegin();
	void StartTick(float _DeltaTime);
	void StartExit();
	void TickBegin();
	void TickTick(float _DeltaTime);
	void TickExit();
	void EndBegin();
	void EndTick(float _DeltaTime);
	void EndExit();

	void CollisionCheck(float _DeltaTime);

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* TentacleRenderer = nullptr;
	UCollision* TentacleCollision = nullptr;
	UStateManager State;
	FVector ThisScale = FVector(64.0f, 120.0f);
	float LifeTime = 0.0f;
};


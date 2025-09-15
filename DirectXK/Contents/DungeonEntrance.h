#pragma once
#include <EngineCore/Actor.h>

class ADungeonEntrance : public AActor
{
	GENERATED_BODY(AActor)
public :
	// constrcuter destructer
	ADungeonEntrance();
	~ADungeonEntrance();

	// delete Function
	ADungeonEntrance(const ADungeonEntrance& _Other) = delete;
	ADungeonEntrance(ADungeonEntrance&& _Other) noexcept = delete;
	ADungeonEntrance& operator=(const ADungeonEntrance& _Other) = delete;
	ADungeonEntrance& operator=(ADungeonEntrance&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	USpriteRenderer* EntranceRenderer = nullptr;
	FVector Position = FVector::Zero;
};


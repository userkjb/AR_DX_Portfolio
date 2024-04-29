#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class UDefaultSceneComponent;
class ADevilChurchWarlock : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ADevilChurchWarlock();
	~ADevilChurchWarlock();

	// delete Function
	ADevilChurchWarlock(const ADevilChurchWarlock& _Other) = delete;
	ADevilChurchWarlock(ADevilChurchWarlock&& _Other) noexcept = delete;
	ADevilChurchWarlock& operator=(const ADevilChurchWarlock& _Other) = delete;
	ADevilChurchWarlock& operator=(ADevilChurchWarlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	UDefaultSceneComponent* Root = nullptr;
};


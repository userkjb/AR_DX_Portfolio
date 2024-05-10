#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class ATownMap : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ATownMap();
	~ATownMap();

	// delete Function
	ATownMap(const ATownMap& _Other) = delete;
	ATownMap(ATownMap&& _Other) noexcept = delete;
	ATownMap& operator=(const ATownMap& _Other) = delete;
	ATownMap& operator=(ATownMap&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* MapImage = nullptr;
	USpriteRenderer* MapCol = nullptr;
};


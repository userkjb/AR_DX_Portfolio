#pragma once
#include <EngineCore/Actor.h>

class UDefaultSceneComponent;
class UTileRenderer;
class ALasleyStageTwoMap : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ALasleyStageTwoMap();
	~ALasleyStageTwoMap();

	// delete Function
	ALasleyStageTwoMap(const ALasleyStageTwoMap& _Other) = delete;
	ALasleyStageTwoMap(ALasleyStageTwoMap&& _Other) noexcept = delete;
	ALasleyStageTwoMap& operator=(const ALasleyStageTwoMap& _Other) = delete;
	ALasleyStageTwoMap& operator=(ALasleyStageTwoMap&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void CreateMapImage();

	UDefaultSceneComponent* Root = nullptr;
	UTileRenderer* TileRenderer = nullptr;
};


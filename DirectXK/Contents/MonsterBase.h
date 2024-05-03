#pragma once
#include <EngineCore/Actor.h>

class UDefaultSceneComponent;
class AMonsterBase : public AActor
{
	GENERATED_BODY(AActor)
public:
	AMonsterBase();
	~AMonsterBase();

	AMonsterBase(const AMonsterBase& _Other) = delete;
	AMonsterBase(AMonsterBase& _Other) noexcept = delete;
	AMonsterBase& operator =(const 	AMonsterBase& _Other) = delete;
	AMonsterBase& operator =(AMonsterBase& _Other)noexcept = delete;

protected :
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :

};


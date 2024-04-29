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

	inline void SetPosition(FVector _Pos)
	{
		SummonPos = _Pos;
	}

	inline void SummonWarlock()
	{
		State.ChangeState("WarlockSummon");
		return;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void CreateAnimtaion();
	void StateInit();

	void SummonBegin();
	void SummonTick(float _DeltaTime);
	void SummonExit();
	void AttackBegin();
	void AttackTick(float _DeltaTime);
	void AttackExit();
	void DieBegin();
	void DieTick(float _DeltaTime);
	void DieExit();
	

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* WarlockRenderer = nullptr;

	UStateManager State;
	FVector SummonPos = FVector::Zero;

	int Hp = 40;
};


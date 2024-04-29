#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class UDefaultSceneComponent;
class AWarlockBlackSphere : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AWarlockBlackSphere();
	~AWarlockBlackSphere();

	// delete Function
	AWarlockBlackSphere(const AWarlockBlackSphere& _Other) = delete;
	AWarlockBlackSphere(AWarlockBlackSphere&& _Other) noexcept = delete;
	AWarlockBlackSphere& operator=(const AWarlockBlackSphere& _Other) = delete;
	AWarlockBlackSphere& operator=(AWarlockBlackSphere&& _Other) noexcept = delete;

	inline void SummonBlackSphere()
	{
		State.ChangeState("DarkSphereSummon");
		return;
	}

	inline void SetSummonBlackSpherePos(FVector _Pos)
	{
		SummonPos = _Pos;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void CreateAnimation();
	void StateInit();

	void DarkSphereSummonBegin();
	void DarkSphereSummonTick(float _DeltaTime);
	void DarkSphereSummonExit();
	void DarkSphereAttackBegin();
	void DarkSphereAttackTick(float _DeltaTime);
	void DarkSphereAttackExit();
	

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* BlackSphereRenderer = nullptr;
	
	UStateManager State;

	FVector SummonPos = FVector::Zero;
};


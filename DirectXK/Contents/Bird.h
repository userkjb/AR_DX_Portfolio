#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class ABird : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ABird();
	~ABird();

	// delete Function
	ABird(const ABird& _Other) = delete;
	ABird(ABird&& _Other) noexcept = delete;
	ABird& operator=(const ABird& _Other) = delete;
	ABird& operator=(ABird&& _Other) noexcept = delete;
		
	inline void BirdCreate()
	{
		State.ChangeState("Create");
		return;
	}

	inline void SetCreateActorPos(FVector _Pos)
	{
		CreateVector = _Pos;
	}

	inline void SetMoveDir(FVector _Dir)
	{
		MoveDir = _Dir;
	}
	
	inline void SetMoveSpeed(float _Speed)
	{
		MoveSpeed = _Speed;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void StateInit();
	void CreateAnimation();

	void NoneBegin();
	void NoneTick(float _DeltaTime);
	void CreateBegin();
	void CreateTick(float _DeltaTime);
	void CreateExit();

	USpriteRenderer* BirdRenderer = nullptr;

	UStateManager State;

	FVector CreateVector = FVector::Zero;
	FVector MoveDir = FVector::Zero;
	float MoveSpeed = 0.0f;
};


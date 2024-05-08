#pragma once
#include <EngineCore/Actor.h>

class ATitleCloud : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ATitleCloud();
	~ATitleCloud();

	// delete Function
	ATitleCloud(const ATitleCloud& _Other) = delete;
	ATitleCloud(ATitleCloud&& _Other) noexcept = delete;
	ATitleCloud& operator=(const ATitleCloud& _Other) = delete;
	ATitleCloud& operator=(ATitleCloud&& _Other) noexcept = delete;

	inline void SetCreateActorPos(FVector _Pos)
	{
		CreateVector = _Pos;
	}

	inline void SetSpriteVal(int _Val)
	{
		SpriteValue = _Val;
	}

	inline void SetCloudRenderOrder(int _Val)
	{
		RenderOrderValue = _Val;
	}

	inline void SetMoveSpeed(float _Speed)
	{
		MoveSpeed = _Speed;
	}
	
	inline void CloudCreate()
	{
		State.ChangeState("Create");
		return;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void StateInit();

	void NoneBegin();
	void NoneTick(float _DeltaTime);
	void CreateBegin();
	void CreateTick(float _DeltaTime);
	void CreateExit();

	USpriteRenderer* CloudRenderer = nullptr;

	UStateManager State;

	FVector CreateVector = FVector::Zero;
	int SpriteValue = 0;
	int RenderOrderValue = 0;
	float MoveSpeed = 0.0f;
};


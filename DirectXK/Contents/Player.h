#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>

class USpriteRenderer;
class UDefaultSceneComponent;
class APlayerWeapon;
class LasleyStageGUI;
class APlayer : public AActor , public std::enable_shared_from_this<APlayer>
{
	GENERATED_BODY(AActor)

	friend APlayerWeapon;
	friend LasleyStageGUI;
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	inline int GetHp() const
	{
		return Hp;
	}
	inline void SetHp(int _Hp)
	{
		Hp = _Hp;
	}

	inline FVector GetPlayerPos() const
	{
		return PlayerPos;
	}

	inline float4 GetPlayerToMouseDir() const
	{
		return PlayerToMouseDir;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	
	void CreateAnimation();
	void StateInit();
	void PlayerMouseDir();
	void DashCountTime(float _DeltaTime);
	void t_DeBugFunction(float _DeltaTime);

	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleEnd();
	void RunBegin();
	void RunTick(float _DeltaTime);
	void RunEnd();
	void JumpBegin();
	void JumpTick(float _DeltaTime);
	void JumpEnd();
	void DashBegin();
	void DashTick(float _DeltaTime);
	void DashEnd();
	void DieBegin();
	void DieTick(float _DeltaTime);
	void DieEnd();

	void MoveUpdate(float _DeltaTime);
	void CalVector();
	void Gravity(float _DeltaTime);
	void CalMoveVector(float _DeltaTime);

	void PixelCheck(float _DeltaTime);

	bool IsGround = false;

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* PlayerRenderer = nullptr;
	UCollision* Collision = nullptr;
	UStateManager State;
	EEngineDir ActorDir = EEngineDir::MAX;
	FVector PlayerPos = FVector::Zero;

	float4 PlayerToMouseDir = float4::Zero;

	FVector CalVectors = FVector::Zero;	
	FVector RunVector = FVector::Zero;
	const float RunSpeed = 400.0f;
	FVector JumpVector = FVector::Zero;
	const FVector JumpPower = FVector::Up * 500.0f;
	bool GUI_Gravity = true;
	FVector GravityVector = FVector::Zero;
	const FVector GravityPower = FVector::Down * 1500.0f;
	//FVector DashVector = FVector::Zero;
	const float DashPower = 750.0f;
	float DashTime = 0.0f;
	float4 DashDir = float4::Zero;

	const float DashCountUp = 3.0f; // 3√ 
	float DashCreationTime = 0.0f;
	float JumpTime = 0.0f;
	int Hp = 0;
	int MaxHp = 0;

	int DashCount = 500; // 2
	int DashCountMax = 500; // 2

	FVector WeaponDir = FVector::Zero;
	std::shared_ptr<APlayerWeapon> Weapone = nullptr;
};


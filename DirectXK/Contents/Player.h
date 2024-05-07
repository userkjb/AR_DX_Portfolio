#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include <queue>

class USpriteRenderer;
class UDefaultSceneComponent;
class APlayerWeapon;
class LasleyStageGUI;
class MyWidget;
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

	inline FVector GetPlayerPos() const
	{
		return PlayerPos;
	}

	inline float4 GetPlayerToMouseDir() const
	{
		return PlayerToMouseDir;
	}

	inline void RecvMapInDoor(float _RunX)
	{
		RecvVector.X = _RunX;
	}

	inline void SetPlayerStateIdleLock()
	{
		State.ChangeState("IdleLock");
		return;
	}
	inline void SetPlayerStateIdle()
	{
		State.ChangeState("Idle");
		return;
	}

	void LevelIsDestroy();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	
	void CreateAnimation();
	void StateInit();
	void PlayerMouseDir();
	/// <summary>
	/// 대쉬 함수
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void DashCountTime(float _DeltaTime);
	/// <summary>
	/// 대쉬 할 때 나오는 잔상 생성 함수.
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void DashSpectrumCalPos(float _DeltaTime);
	void t_DeBugFunction(float _DeltaTime);

	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleEnd();
	void IdleLockBegin();
	void IdleLockTick(float _DeltaTime);
	void IdleLockEnd();
	void RunBegin();
	void RunTick(float _DeltaTime);
	void RunEnd();
	void JumpBegin();
	void JumpTick(float _DeltaTime);
	void JumpEnd();
	void JumpingBegin();
	void JumpingTick(float _DeltaTime);
	void JumpingEnd();
	void DashBegin();
	void DashTick(float _DeltaTime);
	void DashEnd();
	void DieBegin();
	void DieTick(float _DeltaTime);
	void DieEnd();

	void CalVector();
	void Gravity(float _DeltaTime);
	void CalMoveVector(float _DeltaTime);

	void PixelCheck(float _DeltaTime);
	void CollisionCheck(float _DeltaTime);
	void CollisionOff(float _DeltaTime);

	bool IsGround = false;
	bool IsWall = false;
	bool IsHill = false;
#ifdef _DEBUG
	FVector V_Test_PlayerPoint_1 = FVector::Zero;
	FVector V_Test_PlayerPoint_2 = FVector::Zero;
#endif

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* PlayerRenderer = nullptr;
	USpriteRenderer* MouseRendere = nullptr;
	UCollision* PlayerCollision = nullptr;
	EPlayerState ActorState = EPlayerState::Idle;
	UStateManager State;
	MyWidget* Widget = nullptr;
	EEngineDir ActorDir = EEngineDir::MAX;
	FVector PlayerPos = FVector::Zero;

	float4 PlayerToMouseDir = float4::Zero;

	FVector CalVectors = FVector::Zero;
	FVector RunVector = FVector::Zero;
	const float RunSpeed = 500.0f;
	FVector JumpVector = FVector::Zero;
	const FVector JumpPower = FVector::Up * 500.0f;
	bool GUI_Gravity = true;
	FVector GravityVector = FVector::Zero;
	const FVector GravityPower = FVector::Down * 1500.0f;
	
	FVector DashVector = FVector::Zero;
	const float DashPower = 1000.0f;
	const float DashSlowPower = -1000.0f;
	float DashTime = 0.0f;
	float4 DashDir = float4::Zero;

	FVector RecvVector = FVector::One;

	//FVector DashSpectrumPos = FVector::Zero; // 잔상
	std::queue<FVector> DashSpectrumPos; // 잔상 위치 저장 Queue
	float DashSpectrumPosSaveTime = 0.0f;
	float DashCreationTime = 0.0f;
	float JumpTime = 0.0f;

	float CollisionOffTime = 0.0f;
	float RenderTransparencyTime = 0.0f;
	bool IsCollision = true;
	bool Transparency = false;

	FVector WeaponDir = FVector::Zero;
	std::shared_ptr<APlayerWeapon> Weapone = nullptr;
};


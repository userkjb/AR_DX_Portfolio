#pragma once
#include <EngineCore/Actor.h>

class UDefaultSceneComponent;
class USpriteRenderer;
class APlayer;
class AWeaponFX;
class APlayerWeapon : public AActor
{
	GENERATED_BODY(AActor)

	friend APlayer;
public :
	// constrcuter destructer
	APlayerWeapon();
	~APlayerWeapon();

	// delete Function
	APlayerWeapon(const APlayerWeapon& _Other) = delete;
	APlayerWeapon(APlayerWeapon&& _Other) noexcept = delete;
	APlayerWeapon& operator=(const APlayerWeapon& _Other) = delete;
	APlayerWeapon& operator=(APlayerWeapon&& _Other) noexcept = delete;
	
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	inline void SetPlayerToMouseDir(float4 _PlayerToMouseDir)
	{
		PlayerToMouseDir = _PlayerToMouseDir;
	}

	inline void SetWeaponRotation(FVector _Rot)
	{
		WeaponRotation = _Rot;
	}

	inline void SetPlayerDir(EEngineDir _PlayerDir)
	{
		PlayerDir = _PlayerDir;
	}

	void GetPlayerToMouseDir();

	void t_DebugFunction(float _DeltaTime);
	
	/// <summary>
	/// 무기 회전
	/// </summary>
	/// <param name="_DeltaTime">DeltaTime</param>
	void WeaponRotControll(float _DeltaTime);

	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleEnd();
	void SwingBegin();
	void SwingTick(float _DeltaTime);
	void SwingEnd();

	/// <summary>
	/// Player에서 Weapon을 생성 후 해당 함수를 이용해서 Player Actor를 넘겨준다.
	/// </summary>
	/// <param name="_APlayer"></param>
	inline void SetPlayerActor(std::shared_ptr<APlayer> _APlayer)
	{
		PlayerActor = _APlayer;
	}

	//========================================================

	std::shared_ptr<APlayer> PlayerActor = nullptr;

	UDefaultSceneComponent* Root = nullptr;
	float4 PlayerToMouseDir = float4::Zero;
	FVector WeaponRotation = FVector::Zero;

	UStateManager State;
	
	USpriteRenderer* Weapon_Renderer = nullptr;
	std::shared_ptr<AWeaponFX> WeaponFXActor= nullptr;
	const float Range = 100.0f; // 무기 사거리.

	bool b_WeaponUpDownDir = false;
	FVector CurAngle = { 0.0f, 0.0f, 45.0f };
	EEngineDir PlayerDir = EEngineDir::MAX;
};


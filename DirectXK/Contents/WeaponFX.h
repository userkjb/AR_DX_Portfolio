#pragma once
#include <EngineCore/Actor.h>

//class APlayerWeapon;
class UDefaultSceneComponent;
//class APlayerWeapon;
class AWeaponFX : public AActor
{
	GENERATED_BODY(AActor)

	//friend APlayerWeapon;
public :
	// constructer destructer
	AWeaponFX();
	virtual ~AWeaponFX();

	// delete Function
	AWeaponFX(const AWeaponFX& _Other) = delete;
	AWeaponFX(AWeaponFX&& _Other) noexcept = delete;
	AWeaponFX& operator=(const AWeaponFX) = delete;
	AWeaponFX& operator=(AWeaponFX&& _Other) noexcept = delete;

	inline void CreateWeaponFX()
	{
		State.ChangeState("Swing");
		return;
	}

	inline void SetCreatePosition(FVector _Pos)
	{
		InPosition = _Pos;
	}

	inline void SetCreateTotation(FVector _Rot)
	{
		InRotation = _Rot;
	}
	
	inline void SetFXScale(FVector _Scale)
	{
		InScale = _Scale;
	}


protected :
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private :
	void StateInit();
	void CreateAnimation();

	void SwingBegin();
	void SwingTick(float _DeltaTime);
	void SwingExit();

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Weapon_FX_Render = nullptr;
	UCollision* Weapon_FX_Collision = nullptr;
	FVector CreateFX_Pos = FVector::Zero;

	UStateManager State;
	FVector InPosition = FVector::Zero;
	FVector InRotation = FVector::Zero;
	FVector InScale = FVector::Zero;
};


#include "PreCompile.h"
#include "LasleyUI.h"
#include <EngineCore/Image.h>

ULasleyUI::ULasleyUI()
{
}

ULasleyUI::~ULasleyUI()
{
}

void ULasleyUI::BeginPlay()
{
	Super::BeginPlay();

	float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
	ScreenScaleHalf.Y -= 42.0f;
	{
		HpBar_Back = CreateWidget<UImage>(GetWorld(), "BossHpBarBase");
		HpBar_Back->SetupAttachment(this);
		HpBar_Back->SetSprite("BossLifeBack.png");
		HpBar_Back->SetAutoSize(4.0f, true);
		HpBar_Back->SetPosition(FVector(0.0f, -ScreenScaleHalf.Y));
	}
	{
		HpBar_Icon = CreateWidget<UImage>(GetWorld(), "BossHpBarBack");
		HpBar_Icon->SetupAttachment(this);
		HpBar_Icon->SetSprite("BossSkellPortrait.png");
		HpBar_Icon->SetAutoSize(4.0f, true);
		HpBar_Icon->SetPosition(FVector(-204.0f, -ScreenScaleHalf.Y));
	}
	{
		HpBar_HpBar = CreateWidget<UImage>(GetWorld(), "BossHpBar");
		HpBar_HpBar->SetupAttachment(this);
		HpBar_HpBar->SetSprite("PlayerLifeBack2.png");
		//HpBar_HpBar->SetAutoSize(4.0f, true);
		HpBar_HpBar->SetWidgetScale3D(FVector(410.0f, 60.0f, 40.0f));
		HpBar_HpBar->SetPosition(FVector(40.0f, -ScreenScaleHalf.Y));
	}
	{
		HpBar_Base = CreateWidget<UImage>(GetWorld(), "BossHpBarBack");
		HpBar_Base->SetupAttachment(this);
		HpBar_Base->SetSprite("BossLifeBase.png");
		HpBar_Base->SetAutoSize(4.0f, true);
		HpBar_Base->SetPosition(FVector(0.0f, -ScreenScaleHalf.Y));
	}

	AddToViewPort(1);
}

void ULasleyUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == InHit)
	{
		FVector HpBarScale = HpBar_HpBar->GetWidgetScale3D(); // 500
		//int x = GetWeaponDamage; // 25
		//int y = LasleyMaxHp;
		float Cal = (static_cast<float>(GetWeaponDamage) * 100.0f) / static_cast<float>(LasleyMaxHp);

		float Value = (HpBarScale.X * Cal) / 100.0f;

		HpBarScale.X += -Value;
		HpBar_HpBar->SetWidgetScale3D(HpBarScale);
		HpBar_HpBar->AddPosition(FVector(-Value / 2.0f, 0.0f));

		InHit = false;
	}

#ifdef _DEBUG
	if (true == UEngineInput::IsDown('T'))
	{
		FVector HpBarScale = HpBar_HpBar->GetWidgetScale3D(); // 500
		float CalPosition = 1.0f;
		HpBarScale.X += -CalPosition;
		HpBar_HpBar->SetWidgetScale3D(HpBarScale);
		HpBar_HpBar->AddPosition(FVector(-CalPosition / 2.0f, 0.0f));
	}
#endif // _DEBUG
}

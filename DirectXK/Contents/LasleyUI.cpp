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
		// 라슬리 MAX HP, 들어온 대미지
		
		FVector HpBarScale = HpBar_HpBar->GetWidgetScale3D(); // 410
		if (HpMax == 0.0f)
		{
			HpMax = HpBarScale.X;
		}
		
		// 깍아야 할 퍼센트.
		// CalPercent

		// 410에서 계산된 퍼센트 빼기.
		float ApplyValue = HpMax * GetPercent / 100.0f;


		float CurHpValue = HpBarScale.X;
		CurHpValue -= ApplyValue;
		
		if (0.0f >= CurHpValue)
		{
			CurHpValue = 0.0f;
			float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
			HpBar_HpBar->SetWidgetScale3D(FVector(CurHpValue, HpBarScale.Y, HpBarScale.Z));
			HpBar_HpBar->SetPosition(FVector(40.0f, -ScreenScaleHalf.Y));
		}
		else
		{
			HpBar_HpBar->SetWidgetScale3D(FVector(CurHpValue, HpBarScale.Y, HpBarScale.Z));
			HpBar_HpBar->AddPosition(FVector(-ApplyValue / 2.0f, 0.0f));
		}

		InHit = false;
	}

	if (true == ReSet)
	{
		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		ScreenScaleHalf.Y -= 42.0f;
		HpBar_HpBar->SetWidgetScale3D(FVector(410.0f, 60.0f, 40.0f));
		HpBar_HpBar->SetPosition(FVector(40.0f, -ScreenScaleHalf.Y));
		ReSet = false;
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

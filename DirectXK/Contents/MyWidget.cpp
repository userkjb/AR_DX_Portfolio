#include "PreCompile.h"
#include "MyWidget.h"
#include <EngineCore/TextWidget.h>
#include <EngineCore/Image.h>
#include "PlayerStruct.h"

// 하위 위젯들을 관리하는 위젯인것.
MyWidget::MyWidget()
{

}

MyWidget::~MyWidget()
{
}


void MyWidget::BeginPlay()
{
	Super::BeginPlay();
	// UI를 관리하는 개념의 클래스가 된다.
	//{
	//	UImage* Image = CreateWidget<UImage>(GetWorld(), "HpBar");
	//	Image->SetupAttachment(this);
	//	Image->SetSprite("HPBar.png");
	//	Image->SetAutoSize(0.5f, true);
	//	Image->SetPosition({ -400, 300 });
	//}

	//{
	//	UImage* Image = CreateWidget<UImage>(GetWorld(), "HpBar");
	//	Image->SetupAttachment(this);
	//	Image->SetSprite("HPBar.png");
	//	Image->SetAutoSize(0.5f, true);
	//	Image->SetPosition({ 400, 300 });
	//}

	//{
	//	UTextWidget* Image = CreateWidget<UTextWidget>(GetWorld(), "Test");
	//	Image->SetupAttachment(this);
	//	Image->SetFont("궁서");
	//	Image->SetScale(100.0f);
	//	Image->SetColor(Color8Bit::Blue);
	//	Image->SetPosition({ 400, 300 });
	//	Image->SetText("하하하ㅏ허ㅏㅣㅁㅇㄴ러ㅏㅣㄴㅁㅇ러ㅏㅣㅁㄴㅇ");
	//}

	{
		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		ScreenScaleHalf.X -= 148.0f;
		ScreenScaleHalf.Y -= 32.0f;
		HpBar_Base = CreateWidget<UImage>(GetWorld(), "HpLifeBar");
		HpBar_Base->SetupAttachment(this);
		HpBar_Base->SetSprite("PlayerLifeBack2.png");
		HpBar_Base->SetWidgetScale3D((FVector(49.0f, 10.0f))*4.0f);
		ScreenScaleHalf.X -= 38.0f;
		HpBar_Base->SetPosition(FVector(-ScreenScaleHalf.X, ScreenScaleHalf.Y));
		DefaultScale = HpBar_Base->GetWidgetScale3D();
		// 296 / 64
		int a = 0;
	}

	{
		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		ScreenScaleHalf.X -= 148.0f;
		ScreenScaleHalf.Y -= 32.0f;

		HpBar_Ani = CreateWidget<UImage>(GetWorld(), "HpBar");
		//Image->SetupAttachment(this); // 이거 하면 1픽셀 점으로 나옴.
		HpBar_Ani->AddToViewPort(1);
		HpBar_Ani->CreateAnimation("HpBar", "LifeBar", 0.125f, true, 1, 7);
		//HpBar_Ani->SetPosition(FVector(-ScreenScaleHalf.X, ScreenScaleHalf.Y));
		HpBar_Ani->SetPosition(FVector(-350.0f, ScreenScaleHalf.Y));
		HpBar_Ani->SetAutoSize(4.0f, true);
		HpBar_Ani->ChangeAnimation("HpBar");
	}

	{
		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		ScreenScaleHalf.X -= 148.0f;
		ScreenScaleHalf.Y -= 32.0f;
		UImage* Image = CreateWidget<UImage>(GetWorld(), "HpBarBase");
		Image->SetupAttachment(this);
		Image->SetSprite("PlayerLifeBase.png");
		Image->SetPosition(FVector(-ScreenScaleHalf.X, ScreenScaleHalf.Y));
		Image->SetAutoSize(4.0f, true);
	}


	AddToViewPort(1);
}

void MyWidget::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//if (EPlayerStateValue::MaxHp == EPlayerStateValue::Hp)
	//{
	//	HpBar_Ani->SetActive(false);
	//}
	//else
	//{
	//	HpBar_Ani->SetActive(true);
	//}

	if (true == UEngineInput::IsDown('T'))
	{
		DefaultScale.X += -1.0f;
		HpBar_Base->SetWidgetScale3D(DefaultScale);
		HpBar_Base->AddPosition(FVector(-0.5f, 0.0f, 0.0f));
		HpBar_Ani->AddPosition(FVector(-1.0f, 0.0f, 0.0f));
	}

	if (true == UEngineInput::IsDown('P'))
	{
		EPlayerStateValue::Hp -= 10;
	}
}

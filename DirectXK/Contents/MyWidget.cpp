#include "PreCompile.h"
#include "MyWidget.h"
#include <EngineCore/TextWidget.h>
#include <EngineCore/Image.h>

// ���� �������� �����ϴ� �����ΰ�.
MyWidget::MyWidget()
{

}

MyWidget::~MyWidget()
{
}


void MyWidget::BeginPlay()
{
	Super::BeginPlay();
	// UI�� �����ϴ� ������ Ŭ������ �ȴ�.
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
	//	Image->SetFont("�ü�");
	//	Image->SetScale(100.0f);
	//	Image->SetColor(Color8Bit::Blue);
	//	Image->SetPosition({ 400, 300 });
	//	Image->SetText("�����Ϥ��㤿�Ӥ����������Ӥ����������Ӥ�����");
	//}

	{

	}

	// Hp Base
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

	{
		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		ScreenScaleHalf.X -= 148.0f;
		ScreenScaleHalf.Y -= 32.0f;

		HpBar = CreateWidget<UImage>(GetWorld(), "HpBar");
		//Image->SetupAttachment(this); // �̰� �ϸ� 1�ȼ� ������ ����.
		HpBar->AddToViewPort(2);
		HpBar->CreateAnimation("HpBar", "LifeBar", 0.125f, true, 1, 7);
		HpBar->SetPosition(FVector(-ScreenScaleHalf.X, ScreenScaleHalf.Y));
		HpBar->SetAutoSize(4.0f, true);
		//Image->SetWidgetScale3D(FVector(100.0f, 100.0f));
		HpBar->ChangeAnimation("HpBar");
	}


	AddToViewPort(1);
}

void MyWidget::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown('T'))
	{
		HpBar->AddPosition(FVector(1.0f, 0.0f, 0.0f));
	}
}

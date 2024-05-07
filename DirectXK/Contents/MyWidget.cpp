#include "PreCompile.h"
#include "MyWidget.h"
#include <EngineCore/TextWidget.h>
#include <EngineCore/Image.h>
#include "PlayerStruct.h"

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

	// Hp
	{
		float SetPosX = 158.0f;
		float SetPosY = 42.0f;
		{
			float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
			ScreenScaleHalf.X -= SetPosX;
			ScreenScaleHalf.Y -= SetPosY;
			HpBar_Base = CreateWidget<UImage>(GetWorld(), "HpLifeBar");
			HpBar_Base->SetupAttachment(this);
			HpBar_Base->SetSprite("PlayerLifeBack2.png");
			HpBar_Base->SetWidgetScale3D((FVector(49.0f, 10.0f)) * 4.0f);
			ScreenScaleHalf.X -= 38.0f;
			HpBar_Base->SetPosition(FVector(-ScreenScaleHalf.X, ScreenScaleHalf.Y));
			DefaultScale = HpBar_Base->GetWidgetScale3D();
		}

		{
			float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
			ScreenScaleHalf.X -= SetPosX;
			ScreenScaleHalf.Y -= SetPosY;

			HpBar_Ani = CreateWidget<UImage>(GetWorld(), "HpBar");
			//Image->SetupAttachment(this); // �̰� �ϸ� 1�ȼ� ������ ����.
			HpBar_Ani->AddToViewPort(1);
			HpBar_Ani->CreateAnimation("HpBar", "LifeBar", 0.125f, true, 1, 7);
			//HpBar_Ani->SetPosition(FVector(-ScreenScaleHalf.X, ScreenScaleHalf.Y));
			ScreenScaleHalf.X -= 142.0f;
			HpBar_Ani->SetPosition(FVector(-ScreenScaleHalf.X, ScreenScaleHalf.Y));
			HpBar_Ani->SetAutoSize(4.0f, true);
			HpBar_Ani->ChangeAnimation("HpBar");
		}

		{
			float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
			ScreenScaleHalf.X -= SetPosX;
			ScreenScaleHalf.Y -= SetPosY;
			UImage* Image = CreateWidget<UImage>(GetWorld(), "HpBarBase");
			Image->SetupAttachment(this);
			Image->SetSprite("PlayerLifeBase.png");
			Image->SetPosition(FVector(-ScreenScaleHalf.X, ScreenScaleHalf.Y));
			Image->SetAutoSize(4.0f, true);
		}
	}
	
	// Dash
	{
		{
			float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
			ScreenScaleHalf.X -= 30.0f;
			ScreenScaleHalf.Y -= 100.0f;
			Dash_Image_Start = CreateWidget<UImage>(GetWorld(), "DashStart");
			Dash_Image_Start->SetupAttachment(this);
			Dash_Image_Start->SetSprite("DashCountBase_0.png");
			Dash_Image_Start->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
			Dash_Image_Start->SetPosition(FVector(-ScreenScaleHalf.X, ScreenScaleHalf.Y));
		}

		{
			FVector StartPos = Dash_Image_Start->GetWorldPosition();
			float UpdatePos = Dash_Image_Start->GetWidgetScale3D().X;
			UpdatePos -= 2.0f;
			StartPos.X += UpdatePos; // 42.0
			Dash_Base = CreateWidget<UImage>(GetWorld(), "DashBase");
			Dash_Base->SetupAttachment(this);
			Dash_Base->SetSprite("DashCountBase_1.png");
			Dash_Base->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
			Dash_Base->SetPosition(FVector(StartPos.X, StartPos.Y));
		}

		{
			FVector StartPos = Dash_Base->GetWorldPosition();
			float UpdatePos = Dash_Base->GetWidgetScale3D().X;
			UpdatePos += 4.0f;
			StartPos.X += UpdatePos; // 42.0
			Dash_Image_End = CreateWidget<UImage>(GetWorld(), "DashBase");
			Dash_Image_End->SetupAttachment(this);
			Dash_Image_End->SetSprite("DashCountBase_2.png");
			Dash_Image_End->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
			Dash_Image_End->SetPosition(FVector(StartPos.X, StartPos.Y));
		}

		{
			{
				FVector Pos = Dash_Image_Start->GetWorldPosition();
				Pos.X += 4.0f;
				Dash_Count = CreateWidget<UImage>(GetWorld(), "DashCount");
				Dash_Count->SetupAttachment(this);
				Dash_Count->SetSprite("DashCount.png");
				Dash_Count->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
				Dash_Count->SetPosition(Pos);
				Dash_Count->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.5f));
			}

			{
				FVector Pos = Dash_Base->GetWorldPosition();
				Pos.X += 2.0f;
				Dash_Count_2 = CreateWidget<UImage>(GetWorld(), "DashCount");
				Dash_Count_2->SetupAttachment(this);
				Dash_Count_2->SetSprite("DashCount.png");
				Dash_Count_2->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
				Dash_Count_2->SetPosition(Pos);
				Dash_Count_2->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.5f));
			}

			{
				FVector Pos = Dash_Image_End->GetWorldPosition();
				Pos.X -= 2.0f;
				Dash_Count_3 = CreateWidget<UImage>(GetWorld(), "DashCount");
				Dash_Count_3->SetupAttachment(this);
				Dash_Count_3->SetSprite("DashCount.png");
				Dash_Count_3->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
				Dash_Count_3->SetPosition(Pos);
				Dash_Count_3->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}
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

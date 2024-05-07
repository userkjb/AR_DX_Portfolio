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
			//Image->SetupAttachment(this); // 이거 하면 1픽셀 점으로 나옴.
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
			Dash_Image_Mid_1 = CreateWidget<UImage>(GetWorld(), "DashBase");
			Dash_Image_Mid_1->SetupAttachment(this);
			Dash_Image_Mid_1->SetSprite("DashCountBase_1.png");
			Dash_Image_Mid_1->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
			Dash_Image_Mid_1->SetPosition(FVector(StartPos.X, StartPos.Y));
		}
		{
			FVector StartPos = Dash_Image_Mid_1->GetWorldPosition();
			float UpdatePos = Dash_Image_Mid_1->GetWidgetScale3D().X;
			//UpdatePos += 2.0f;
			StartPos.X += UpdatePos; // 42.0
			Dash_Image_Mid_2 = CreateWidget<UImage>(GetWorld(), "DashBase");
			Dash_Image_Mid_2->SetupAttachment(this);
			Dash_Image_Mid_2->SetSprite("DashCountBase_1.png");
			Dash_Image_Mid_2->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
			Dash_Image_Mid_2->SetPosition(FVector(StartPos.X, StartPos.Y));
		}

		{
			FVector StartPos = Dash_Image_Mid_2->GetWorldPosition();
			float UpdatePos = Dash_Image_Mid_2->GetWidgetScale3D().X;
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
				Dash_Count_1 = CreateWidget<UImage>(GetWorld(), "DashCount");
				Dash_Count_1->SetupAttachment(this);
				Dash_Count_1->SetSprite("DashCount.png");
				Dash_Count_1->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
				Dash_Count_1->SetPosition(Pos);
				Dash_Count_1->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.5f));
			}

			{
				FVector Pos = Dash_Image_Mid_1->GetWorldPosition();
				Pos.X += 2.0f;
				Dash_Count_2 = CreateWidget<UImage>(GetWorld(), "DashCount");
				Dash_Count_2->SetupAttachment(this);
				Dash_Count_2->SetSprite("DashCount.png");
				Dash_Count_2->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
				Dash_Count_2->SetPosition(Pos);
				Dash_Count_2->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.5f));
			}
			{
				FVector Pos = Dash_Image_Mid_2->GetWorldPosition();
				Pos.X += 2.0f;
				Dash_Count_3 = CreateWidget<UImage>(GetWorld(), "DashCount");
				Dash_Count_3->SetupAttachment(this);
				Dash_Count_3->SetSprite("DashCount.png");
				Dash_Count_3->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
				Dash_Count_3->SetPosition(Pos);
				Dash_Count_3->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.5f));
			}

			{
				FVector Pos = Dash_Image_End->GetWorldPosition();
				Pos.X -= 2.0f;
				Dash_Count_4 = CreateWidget<UImage>(GetWorld(), "DashCount");
				Dash_Count_4->SetupAttachment(this);
				Dash_Count_4->SetSprite("DashCount.png");
				Dash_Count_4->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
				Dash_Count_4->SetPosition(Pos);
				Dash_Count_4->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.5f));
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

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
	CreateHpBar();
	
	// Dash
	CreateDashBar();
	//CreateDashBar_v2();

	{
		Hit = CreateWidget<UImage>(GetWorld(), "HpLifeBar");
		Hit->SetupAttachment(this);
		Hit->SetSprite("Hit.png");
		Hit->SetAutoSize(4.0f, true);
		Hit->AddToViewPort(4);
	}

	

	AddToViewPort(1);

	DashCountTime = 0.0f;
}

void MyWidget::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == InDamage)
	{
		float CalPosition = 1.0f; // InDamageValue
		DefaultScale.X += -CalPosition; // 196.0f
		HpBar_Base->SetWidgetScale3D(DefaultScale);
		HpBar_Base->AddPosition(FVector(-(CalPosition / 2.0f), 0.0f, 0.0f));
		HpBar_Ani->AddPosition(FVector(-CalPosition, 0.0f, 0.0f));

		InDamage = false;
	}

	if (true == InHit)
	{
		HitAlpha -= _DeltaTime * 0.5f;
		Hit->SetMulColor(float4(1.0f, 1.0f, 1.0f, HitAlpha));

		if (0.0f > HitAlpha)
		{
			HitAlpha = 1.0f;
			InHit = false;
		}
	}
	else
	{
		Hit->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.0f));
	}
}

void MyWidget::CreateHpBar()
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

void MyWidget::CreateDashBar()
{
	for (size_t i = 0; i < static_cast<size_t>(EPlayerStateValue::DashCountMax); i++)
	{
		if (i == 0)
		{
			float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
			ScreenScaleHalf.X -= 30.0f;
			ScreenScaleHalf.Y -= 100.0f;
			UImage* Dash_Image = CreateWidget<UImage>(GetWorld(), "DashStart");
			Dash_Image->SetupAttachment(this);
			Dash_Image->SetSprite("DashCountBase_0.png");
			Dash_Image->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
			Dash_Image->SetPosition(FVector(-ScreenScaleHalf.X, ScreenScaleHalf.Y));

			FVector Pos = Dash_Image->GetWorldPosition();
			Pos.X += 4.0f;
			UImage* Dash_Count = CreateWidget<UImage>(GetWorld(), "DashCount");
			Dash_Count->SetupAttachment(this);
			Dash_Count->SetSprite("DashCount.png");
			Dash_Count->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
			Dash_Count->SetPosition(Pos);
			Dash_Count->SetMulColor(float4(1.0f, 1.0f, 1.0f, 1.0f));

			Dash_Base_Images.push_back(std::make_pair(Dash_Image, Dash_Count));
		}
		else if (i != 0 && i != static_cast<size_t>(EPlayerStateValue::DashCountMax) - 1)
		{
			FVector StartPos = Dash_Base_Images[i - 1].first->GetWorldPosition();
			float UpdatePos = Dash_Base_Images[i - 1].first->GetWidgetScale3D().X;
			UpdatePos -= 2.0f;
			StartPos.X += UpdatePos; // 42.0
			UImage* Dash_Image_Mid = CreateWidget<UImage>(GetWorld(), "DashBase");
			Dash_Image_Mid->SetupAttachment(this);
			Dash_Image_Mid->SetSprite("DashCountBase_1.png");
			Dash_Image_Mid->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
			Dash_Image_Mid->SetPosition(FVector(StartPos.X, StartPos.Y));

			FVector Pos = Dash_Image_Mid->GetWorldPosition();
			Pos.X += 2.0f;
			UImage* Dash_Count_Mid = CreateWidget<UImage>(GetWorld(), "DashCount");
			Dash_Count_Mid->SetupAttachment(this);
			Dash_Count_Mid->SetSprite("DashCount.png");
			Dash_Count_Mid->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
			Dash_Count_Mid->SetPosition(Pos);
			Dash_Count_Mid->SetMulColor(float4(1.0f, 1.0f, 1.0f, 1.0f));

			Dash_Base_Images.push_back(std::make_pair(Dash_Image_Mid, Dash_Count_Mid));
		}
		else if (i == static_cast<size_t>(EPlayerStateValue::DashCountMax) - 1)
		{
			FVector StartPos = Dash_Base_Images[i - 1].first->GetWorldPosition();
			float UpdatePos = Dash_Base_Images[i - 1].first->GetWidgetScale3D().X;
			UpdatePos += 4.0f;
			StartPos.X += UpdatePos; // 42.0
			UImage* Dash_Image_End = CreateWidget<UImage>(GetWorld(), "DashBase");
			Dash_Image_End->SetupAttachment(this);
			Dash_Image_End->SetSprite("DashCountBase_2.png");
			Dash_Image_End->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
			Dash_Image_End->SetPosition(FVector(StartPos.X, StartPos.Y));

			FVector Pos = Dash_Image_End->GetWorldPosition();
			Pos.X -= 2.0f;
			UImage* Dash_Count_End = CreateWidget<UImage>(GetWorld(), "DashCount");
			Dash_Count_End->SetupAttachment(this);
			Dash_Count_End->SetSprite("DashCount.png");
			Dash_Count_End->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
			Dash_Count_End->SetPosition(Pos);
			Dash_Count_End->SetMulColor(float4(1.0f, 1.0f, 1.0f, 1.0f));

			Dash_Base_Images.push_back(std::make_pair(Dash_Image_End, Dash_Count_End));
		}
	}
}

void MyWidget::CreateDashBar_v2()
{
	float DashBar_X_Right_Margin = 14.0f;

	float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
	ScreenScaleHalf.X -= DashBar_X_Right_Margin; // 640
	ScreenScaleHalf.Y -= 100.0f; // 340

	// Start
	{
		UImage* StartDashBar = CreateWidget<UImage>(GetWorld(), "DashBase");
		StartDashBar->SetupAttachment(this);
		StartDashBar->SetSprite("DashBaseLeftEnd.png");
		StartDashBar->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
		StartDashBar->SetPosition(FVector(-ScreenScaleHalf.X, ScreenScaleHalf.Y));
	}


}

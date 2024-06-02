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
		HpBarUpdate(_DeltaTime);
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

	if (true == IsCreate)
	{
		UpdateDashBar(_DeltaTime);
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
			if (EPlayerStateValue::DashCount != EPlayerStateValue::DashCountMax)
			{
				Dash_Count_End->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.0f));
			}
			else
			{
				Dash_Count_End->SetMulColor(float4(1.0f, 1.0f, 1.0f, 1.0f));
			}

			Dash_Base_Images.push_back(std::make_pair(Dash_Image_End, Dash_Count_End));
		}
	}
	IsCreate = true;
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

void MyWidget::UpdateDashBar(float _DeltaTime)
{
	if (EPlayerStateValue::DashCount != EPlayerStateValue::DashCountMax)
	{
		DashCountTime += _DeltaTime;
		int DashCountIndex = EPlayerStateValue::DashCount;
		Dash_Base_Images[DashCountIndex].second->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.0f));
	}

	if (DashCountTime >= EPlayerStateValue::DashCountUpTime)
	{
		int DashCountIndex = EPlayerStateValue::DashCount;
		Dash_Base_Images[DashCountIndex].second->SetMulColor(float4(1.0f, 1.0f, 1.0f, 1.0f));
		EPlayerStateValue::DashCount++;
		DashCountTime = 0.0f;
	}
	else if (DashCountTime >= EPlayerStateValue::DashCountUpTime / 2.0f)
	{
		int DashCountIndex = EPlayerStateValue::DashCount;
		int PlusCount = DashCountIndex + 1;
		if (PlusCount != EPlayerStateValue::DashCountMax)
		{
			Dash_Base_Images[PlusCount].second->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.0f));
		}
		Dash_Base_Images[DashCountIndex].second->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.5f));
	}
}

void MyWidget::HpBarUpdate(float _DeltaTime)
{
	FVector DefaultScale = HpBar_Base->GetWidgetScale3D(); // 196
	if (HpBarMax == 0.0f)
	{
		HpBarMax = DefaultScale.X;
	}

	float ApplyValue = HpBarMax * InDamagePercent / 100.0f;

	float CurHpValue = DefaultScale.X;
	CurHpValue -= ApplyValue;

	if (0.0f >= CurHpValue)
	{
		CurHpValue = 0.0f;
		float4 ScreenScaleHale = GEngine->EngineWindow.GetWindowScale().Half2D();
		HpBar_Base->SetWidgetScale3D(FVector(CurHpValue, DefaultScale.Y, DefaultScale.Z));
		HpBar_Base->SetPosition(FVector(-ApplyValue / 2.0f, 0.0f));

		float4 ScreenScaleHalf = GEngine->EngineWindow.GetWindowScale().Half2D();
		float4 HpBar_AniScale = HpBar_Ani->GetWidgetScale3D();
		HpBar_AniScale.X = 0.0f;
		HpBar_Ani->SetWidgetScale3D(FVector(HpBar_AniScale.X, DefaultScale.Y, DefaultScale.Z));
		HpBar_Ani->SetPosition(FVector(-ScreenScaleHalf.X, ScreenScaleHalf.Y));
	}
	else
	{
		HpBar_Base->SetWidgetScale3D(FVector(CurHpValue, DefaultScale.Y, DefaultScale.Z));
		HpBar_Base->AddPosition(FVector(-ApplyValue / 2.0f, 0.0f));
		HpBar_Ani->AddPosition(FVector(-ApplyValue, 0.0f));
	}

	InDamage = false;
}

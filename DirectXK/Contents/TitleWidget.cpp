#include "PreCompile.h"
#include "TitleWidget.h"
#include <EngineCore/Image.h>

UTitleWidget::UTitleWidget()
{
}

UTitleWidget::~UTitleWidget()
{
}

void UTitleWidget::BeginPlay()
{
	Super::BeginPlay();

	GameStart = CreateWidget<UImage>(GetWorld(), "GameStart");
	GameStart->AddToViewPort(1);
	GameStart->SetupAttachment(this);
	GameStart->SetSprite("PlayOff_Kor.png");
	GameStart->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
	//GameStart->SetScale(FVector(146.0f, 48.0f));
	GameStart->SetPosition(FVector(0.0f, -100.0f));

	GameStart->SetHover([=]()
		{
			IsGameStartHover = true;
		}
	);
	GameStart->SetUnHover([=]()
		{
			IsGameStartHover = false;
		}
	);
	GameStart->SetDown([=]()
		{
			IsGameStartDown = true;
		}
	);



	AddToViewPort(1);
}

void UTitleWidget::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsGameStartHover)
	{
		GameStart->SetSprite("PlayOn_Kor.png");

		if (true == IsGameStartDown)
		{
			GEngine->ChangeLevel("LasleyLevel");
		}
	}
	else
	{
		GameStart->SetSprite("PlayOff_Kor.png");
	}


	//GameStart_F->SetDown([=]()
	//	{
	//		int a = 0;
	//		GEngine->ChangeLevel("");
	//		return;
	//	}
	//);
}

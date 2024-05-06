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

	//GameStart_F->SetSprite("");
	//GameStart_F->SetAutoSize(4.0f, true);
}

void UTitleWidget::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//GameStart_F->SetHover([=]()
	//	{
	//		int a = 0;
	//	}
	//);

	//GameStart_F->SetDown([=]()
	//	{
	//		int a = 0;
	//		GEngine->ChangeLevel("");
	//		return;
	//	}
	//);
}

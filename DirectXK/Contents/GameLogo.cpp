#include "PreCompile.h"
#include "GameLogo.h"
#include <EngineCore/DefaultSceneComponent.h>


AGameLogo::AGameLogo()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>("LogoRenderer");
	LogoRenderer->SetupAttachment(Root);
	LogoRenderer->SetOrder(ERenderOrder::TitleImage);
}

AGameLogo::~AGameLogo()
{
}

void AGameLogo::BeginPlay()
{
	Super::BeginPlay();

	//SetActorScale3D(FVector(156.0f, 75.0f, 0.0f));

	LogoRenderer->SetSprite("MainLogo1.png"); // 이미지 단장.
	LogoRenderer->SetAutoSize(UContentsConstValue::AutoSizeValue, true);
	//LogoRenderer->CreateAnimation("GameTitleLogo", "GameTitleLogo", 0.25f);
	//LogoRenderer->ChangeAnimation("GameTitleLogo");
}

void AGameLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

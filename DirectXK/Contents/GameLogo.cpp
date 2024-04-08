#include "PreCompile.h"
#include "GameLogo.h"

AGameLogo::AGameLogo()
{
	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>("LogoRenderer");
}

AGameLogo::~AGameLogo()
{
}

void AGameLogo::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(156.0f, 75.0f, 0.0f));

	//LogoRenderer->SetSprite("Idle.png"); // 이미지 단장.

	LogoRenderer->CreateAnimation("GameTitleLogo", "GameTitleLogo", 0.25f);

	LogoRenderer->ChangeAnimation("GameTitleLogo");
}

void AGameLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

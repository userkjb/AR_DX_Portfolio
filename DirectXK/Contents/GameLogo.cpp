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

	SetActorScale3D(FVector(500.0f, 500.0f, 100.0f));

	//LogoRenderer->SetSprite("Idle", 0);


	LogoRenderer->CreateAnimation("Idle", "Idle", 0.25f);
	LogoRenderer->CreateAnimation("Run", "Run", 0.25f);


	LogoRenderer->ChangeAnimation("Idle");
}

void AGameLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown('X'))
	{
		LogoRenderer->ChangeAnimation("Run");
	}
}

#include "PreCompile.h"
#include "TestActor.h"

#include <EngineCore/Renderer.h>
#include <EngineCore/DefaultSceneComponent.h>

ATestActor::ATestActor()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<URenderer>("Renderer");
	Renderer->SetMesh("Rect");
	// 메테리얼을 해주는순간
	// 메테리얼은 안에 버텍스쉐이더와 픽셀쉐이더를 둘다 들고 있죠.
	// 색깔  머티리얼그자체에 세팅해준다.
	// 
	Renderer->SetMaterial("2DImage");
	Renderer->SetupAttachment(Root);

	// Renderer->세팅픽셀쉐이더상수버퍼();
	// Renderer->세팅버텍스쉐이더상수버퍼();
	SetRoot(Root);
}

ATestActor::~ATestActor()
{
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(300.0f, 300.0f, 100.0f));

	// 안해주면 터져야한다.
	Renderer->Resources->SettingConstantBuffer("OutPutColor", Color);
	// 내부에서 샘플러도 같이 찾을
	Renderer->Resources->SettingTexture("Image", "CharIdle0.png", "POINT");

	// 컴포넌트 리턴 예제
	{
		std::vector<std::shared_ptr<URenderer>> Renders = GetComponentToClass<URenderer>();
	}
}

void ATestActor::Tick(float _DeltaTime)
{
	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);

	float Speed = 100.0f;

	if (true == UEngineInput::IsPress('A'))
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}

	if (true == UEngineInput::IsPress('D'))
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	if (true == UEngineInput::IsPress('W'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}

	if (true == UEngineInput::IsPress('S'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
	}

	if (true == UEngineInput::IsPress(VK_NUMPAD1))
	{
		Color.X += _DeltaTime;
	}

	if (true == UEngineInput::IsPress(VK_NUMPAD2))
	{
		Color.X -= _DeltaTime;
	}

	if (true == UEngineInput::IsPress(VK_NUMPAD4))
	{
		Color.Y += _DeltaTime;
	}

	if (true == UEngineInput::IsPress(VK_NUMPAD5))
	{
		Color.Y -= _DeltaTime;
	}

	if (true == UEngineInput::IsPress(VK_NUMPAD7))
	{
		Color.Z += _DeltaTime;
	}

	if (true == UEngineInput::IsPress(VK_NUMPAD8))
	{
		Color.Z -= _DeltaTime;
	}

	// Renderer->SetConstanctBuffer("Ftransform", GetTransform());


}
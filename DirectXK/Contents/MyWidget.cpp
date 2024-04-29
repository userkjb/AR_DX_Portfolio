#include "PreCompile.h"
#include "MyWidget.h"
#include <EngineCore/TextWidget.h>
#include <EngineCore/Image.h>

// 하위 위젯들을 관리하는 위젯인것.
MyWidget::MyWidget()
{

}

MyWidget::~MyWidget()
{
}


void MyWidget::BeginPlay()
{
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

	{
		UTextWidget* Image = CreateWidget<UTextWidget>(GetWorld(), "Test");
		Image->SetupAttachment(this);
		Image->SetFont("궁서");
		Image->SetScale(100.0f);
		Image->SetColor(Color8Bit::Blue);
		Image->SetPosition({ 400, 300 });
		Image->SetText("하하하ㅏ허ㅏㅣㅁㅇㄴ러ㅏㅣㄴㅁㅇ러ㅏㅣㅁㄴㅇ");
	}


	AddToViewPort(1);
}

#pragma once
#include <EngineCore/Widget.h>

// Ό³Έν :
class MyWidget : public UWidget
{
public:
	// constrcuter destructer
	MyWidget();
	~MyWidget();

	// delete Function
	MyWidget(const MyWidget& _Other) = delete;
	MyWidget(MyWidget&& _Other) noexcept = delete;
	MyWidget& operator=(const MyWidget& _Other) = delete;
	MyWidget& operator=(MyWidget&& _Other) noexcept = delete;

protected:
	void BeginPlay();

private:

};


#include <Windows.h>
#include <string_view>

#include <EnginePlatform/EngineWindow.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//	LeakCheck; 
	UEngineWindow NewWindow;
	NewWindow.Open();

	UEngineWindow::WindowMessageLoop(nullptr, nullptr);
}
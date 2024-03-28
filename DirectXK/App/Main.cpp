#include "PreCompile.h"
#include <Windows.h>
#include <string_view>

#include <EngineCore/EngineCore.h>
#include <Contents/ContentsCore.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")
#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "Contents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UEngineCore::Start<UContentsCore>(hInstance);
}
#include "PreCompile.h"
#include "EngineCore.h"
#include "EngineOption.h"
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>

#include <EnginePlatform/EngineSound.h>
#include <EnginePlatform/EngineInput.h>

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

UEngineCore* GEngine = nullptr;

void UEngineCore::EngineStart(HINSTANCE _Inst)
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");

	FEngineOption Option;
	if (false == Dir.IsFile("EngineOption.EData"))
	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		Option.Serialize(Ser);

		File.Open(EIOOpenMode::Write, EIODataType::Text);
		File.Save(Ser);
	}

	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		File = Dir.GetPathFromFile("EngineOption.EData");
		File.Open(EIOOpenMode::Read, EIODataType::Text);
		File.Load(Ser);
		Option.DeSerialize(Ser);
	}

	EngineWindow.Open(Option.WindowTitle);
	EngineWindow.SetWindowScale(Option.WindowScale);

	UserCorePtr->Initialize();

	// 사운드 체크.
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.MoveToSearchChild("Sound");
		std::list<UEngineFile> Files = Dir.AllFile({ ".mp3" });

		for (UEngineFile File : Files)
		{
			UEngineSound::Load(File.GetFullPath());
		}

		UEngineSound::SoundPlay("Ready.mp3");
	}

	UEngineWindow::WindowMessageLoop(
		nullptr,
		nullptr
		//std::bind(&UEngineCore::Update, &Core),
		//std::bind(&UEngineCore::End, &Core)
	);
}
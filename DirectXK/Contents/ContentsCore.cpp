#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineEditorGUI.h>
#include <EngineCore/EngineFont.h>

#include "TestGameMode.h"
#include "GameStartGameMode.h"
#include "TitleGameMode.h"
#include "LasleyGameMode.h"
#include "ContentsGUI.h"
#include "MapEditorGUI.h"
#include "LasleyStageBossGM.h"

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::Initialize()
{
	{
		UEngineEditorGUI::CreateEditorWindow<ContentsGUI>("Contents");
		UEngineEditorGUI::CreateEditorWindow<MapEditorGUI>("MapEditor");
	}

	// Text Ãâ·Â Test
	{
		UEngineFont::Load("±Ã¼­");
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\MouseCursor");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\MapObject");
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}
	}

	GEngine->CreateLevel<ATestGameMode>("TestGameMode");
	//GEngine->ChangeLevel("PlayLevel");
	//GEngine->CreateLevel<AGameStartGameMode>("GameStartGameMode");
	//GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<ALasleyGameMode>("LasleyLevel");
	GEngine->CreateLevel<ALasleyStageBossGM>("LasleyLevelBoss");

	GEngine->ChangeLevel("LasleyLevel");
}
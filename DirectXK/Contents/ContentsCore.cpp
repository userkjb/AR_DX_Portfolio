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
#include "LasleyStageTwoGM.h"

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

	// Text ��� Test
	{
		UEngineFont::Load("�ü�");
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

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\UI");
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\UI\\LifeBar");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\UI\\DashBar");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}
	}

	GEngine->CreateLevel<ATestGameMode>("TestGameMode");
	//GEngine->ChangeLevel("PlayLevel");
	//GEngine->CreateLevel<AGameStartGameMode>("GameStartGameMode");
	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<ALasleyGameMode>("LasleyLevel");
	GEngine->CreateLevel<ALasleyStageBossGM>("LasleyLevelBoss");
	GEngine->CreateLevel<ALasleyStageTwoGM>("LasleyLevelTwo");

	GEngine->ChangeLevel("TitleLevel");
	//GEngine->ChangeLevel("LasleyLevelTwo");
}
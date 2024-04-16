#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineSprite.h>

//#include "PlayGameMode.h"
#include "GameStartGameMode.h"
#include "TitleGameMode.h"
#include "LasleyGameMode.h"

#include <EngineCore/EngineEditorGUI.h>
#include "ContentsGUI.h"
#include "MapEditorGUI.h"

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::Initialize()
{
	{
		UEngineEditorGUI::CreateEditorWindow<ContentsGUI>("GIU");
		UEngineEditorGUI::CreateEditorWindow<MapEditorGUI>("Map");
	}

	//GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	//GEngine->ChangeLevel("PlayLevel");
	//GEngine->CreateLevel<AGameStartGameMode>("GameStartGameMode");
	//GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<ALasleyGameMode>("LasleyLevel");

	GEngine->ChangeLevel("LasleyLevel");
}
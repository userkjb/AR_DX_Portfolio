#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineSprite.h>

#include "TestGameMode.h"
#include "GameStartGameMode.h"
#include "TitleGameMode.h"
#include "LasleyGameMode.h"

#include <EngineCore/EngineEditorGUI.h>
#include "ContentsGUI.h"
#include "MapEditorGUI.h"
#include "LasleyStageGUI.h"

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
		UEngineEditorGUI::CreateEditorWindow<LasleyStageGUI>("LasleyStage");
	}

	GEngine->CreateLevel<ATestGameMode>("TestGameMode");
	//GEngine->ChangeLevel("PlayLevel");
	//GEngine->CreateLevel<AGameStartGameMode>("GameStartGameMode");
	//GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<ALasleyGameMode>("LasleyLevel");

	GEngine->ChangeLevel("LasleyLevel");
}
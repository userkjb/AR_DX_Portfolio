#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineSprite.h>

//#include "PlayGameMode.h"
#include "TitleGameMode.h"
#include "LasleyGameMode.h"

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::Initialize()
{
	//GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	//GEngine->ChangeLevel("PlayLevel");
	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<ALasleyGameMode>("LasleyLevel");

	GEngine->ChangeLevel("LasleyLevel");
}
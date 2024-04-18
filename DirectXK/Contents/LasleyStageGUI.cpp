#include "PreCompile.h"
#include "LasleyStageGUI.h"

LasleyStageGUI::LasleyStageGUI()
{
}

LasleyStageGUI::~LasleyStageGUI()
{
}

void LasleyStageGUI::Init()
{
}

void LasleyStageGUI::Tick(ULevel* _Level, float _DeltaTime)
{
	Super::Tick(_Level, _DeltaTime);

	std::string LevelName = _Level->GetName();
	if ("LasleyLevel" == LevelName)
	{
		On();
	}
	else
	{
		Off();
	}
}

void LasleyStageGUI::OnGui(ULevel* _Level, float _DeltaTime)
{
}
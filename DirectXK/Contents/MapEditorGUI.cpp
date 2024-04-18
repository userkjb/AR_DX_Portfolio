#include "PreCompile.h"
#include "MapEditorGUI.h"
#include "TileMapLevel.h"
#include <EngineCore/TileRenderer.h>
#include "TileMap.h"
#include <EngineCore/Camera.h>

#include <xmllite.h>
#include <Shlwapi.h>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "xmllite.lib")

MapEditorGUI::MapEditorGUI()
{

}

MapEditorGUI::~MapEditorGUI()
{
}

void MapEditorGUI::Init()
{
}

void MapEditorGUI::Tick(ULevel* _Level, float _DeltaTime)
{
	Super::Tick(_Level, _DeltaTime);

	if (true == UEngineInput::IsDown(VK_F8)) // F8
	{
		if (MapEditorCamera == true)
		{
			MapEditorCamera = false;
			//_Level->GetMainCamera()->SetActorLocation({ 0.0f, 0.0f, -500.0f });
		}
		else
		{
			MapEditorCamera = true;
		}
	}
	// ī�޶�.
	if(MapEditorCamera == true)
	{
		_Level->GetMainCamera();
		float Speed = 500.0f;
		if (true == UEngineInput::IsPress('A'))
		{
			_Level->GetMainCamera()->AddActorLocation(float4::Left * _DeltaTime * Speed);
		}

		if (true == UEngineInput::IsPress('D'))
		{
			_Level->GetMainCamera()->AddActorLocation(float4::Right * _DeltaTime * Speed);
		}

		if (true == UEngineInput::IsPress('W'))
		{
			_Level->GetMainCamera()->AddActorLocation(float4::Up * _DeltaTime * Speed);
		}

		if (true == UEngineInput::IsPress('S'))
		{
			_Level->GetMainCamera()->AddActorLocation(float4::Down * _DeltaTime * Speed);
		}
	}


	std::string LevelName = _Level->GetName();

	if ("TestGameMode" == _Level->GetName())
	{
		On();
	}
	else
	{
		Off();
	}

	std::shared_ptr<AGameMode> Mode = _Level->GetGameMode();

	ATileMapLevel* Ptr = dynamic_cast<ATileMapLevel*>(Mode.get());

	if (nullptr == Ptr)
	{
		return;
	}

	UTileRenderer* TileRenderer = Ptr->TileMap->TileRenderer;

	if (true == UEngineInput::IsPress(VK_LBUTTON))
	{
		float4 MousePos = GEngine->EngineWindow.GetScreenMousePos();
		MousePosWorld = _Level->GetMainCamera()->ScreenPosToWorldPos(MousePos);

		TileRenderer->SetTile(MousePosWorld, SelectSpriteIndex);
	}
}

void MapEditorGUI::OnGui(ULevel* _Level, float _Delta)
{

	float4 MousePos = GEngine->EngineWindow.GetScreenMousePos();
	MousePosWorld = _Level->GetMainCamera()->ScreenPosToWorldPos(MousePos);

	std::shared_ptr<AGameMode> Mode = _Level->GetGameMode();

	ATileMapLevel* Ptr = dynamic_cast<ATileMapLevel*>(Mode.get());

	if (nullptr == Ptr)
	{
		return;
	}

	UTileRenderer* TileRenderer = Ptr->TileMap->TileRenderer;


	ImGui::InputFloat2("TileSize", &InputTileSize.X);
	ImGui::InputInt2("Height and Width", InputHWValue);

	// Ÿ�� ũ�� ����
	// Ÿ�� ���� x
	// Ÿ�� ���� y�� 
	// ��������Ʈ ����.
	// ����.
	{
		if (true == ImGui::Button("Create"))
		{
			if (InputTileSize.X == 0.0f || InputTileSize.Y == 0.0f)
			{
				IsCreateImage = false;
			}
			else
			{
				TileRenderer->CreateTileMap("Map4X(64).png", { InputTileSize.X, InputTileSize.Y }, InputHWValue[0], InputHWValue[1], 0);
				IsCreateImage = true;
			}
		}
		if (IsCreateImage)
		{
			Str_CreateImage = "True!!!";
		}
		else
		{
			Str_CreateImage = "False...";
		}
		ImGui::Text(std::format("Create Image : {}", Str_CreateImage).c_str());
	}

	// Save
	{
		if (true == ImGui::Button("Data"))
		{
			TileData = TileRenderer->GetTileMapData();
		}

		// File Save
		//UEngineDirectory Dir;
		//Dir.MoveToSearchChild("Config\\TileData");
	}

	// Save Data To Create
	{ 
		if (true == ImGui::Button("DataToCreate"))
		{
			// File Load
			//-------------------------------------

		}
	}

	ImGui::Text(("WorldMouse : " + MousePosWorld.ToString()).c_str());
	float4 Index = TileRenderer->ConvertTileIndex(MousePosWorld);
	ImGui::Text(("TileIndexPos : " + Index.ToString()).c_str());
	ImGui::Text(std::format("Index : {} {}", Index.iX(), Index.iY()).c_str());


	std::shared_ptr<UEngineSprite> Sprite = UEngineSprite::FindRes("Map4X(64).png");


	// ���̷�Ʈ ����̽���
	// ���̷�Ʈ ���ؽ�
	// imgui�� ���ο��� �ڽ��� ���̴��� ����մϴ�.

	// imgui���� ����ϴ� ���̴��� �� �ؽ�ó�� ����.
	// ImVec2

	// IMgui�� ������ char* Eventüũ�� �մϴ�;
	if (SelectSpriteIndex != -1)
	{
		FSpriteInfo Info = Sprite->GetSpriteInfo(SelectSpriteIndex);

		ImVec2 UV0 = { Info.CuttingPosition.X, Info.CuttingPosition.Y };
		ImVec2 UV1 = { Info.CuttingSize.X, Info.CuttingSize.Y };

		UV1.x = UV1.x + UV0.x;
		UV1.y = UV1.y + UV0.y;

		ImGui::ImageButton("Select", Info.Texture->GetSRV(), { 100, 100 }, UV0, UV1);
	}
	else
	{
		ImGui::ImageButton("Select", nullptr, { 100, 100 });
	}

	ImGui::BeginChild("TileSelect", { 0, 0 }, false, ImGuiWindowFlags_HorizontalScrollbar);


	for (int i = 0; i < Sprite->GetInfoSize(); i++)
	{
		FSpriteInfo Info = Sprite->GetSpriteInfo(i);

		ImVec2 UV0 = { Info.CuttingPosition.X, Info.CuttingPosition.Y };
		ImVec2 UV1 = { Info.CuttingSize.X, Info.CuttingSize.Y };

		UV1.x = UV1.x + UV0.x;
		UV1.y = UV1.y + UV0.y;

		std::string Text = std::to_string(i);

		// �ٹٲ��� �ڵ����� ���ش�.
		if (true == ImGui::ImageButton(Text.c_str(), Info.Texture->GetSRV(), { 64, 64 }, UV0, UV1))
		{
			SelectSpriteIndex = i;
		}

		if ((i + 1) % 5)
		{
			ImGui::SameLine();
		}
	}

	// Index ���� ������ ��������Ʈ

	//ImGui::TextUnformatted("child_2");
	//ImGui::GetWindowDrawList()->AddLine({ 0, 0 }, { 500, 500 }, 0xFFFFFFFF);
	//ImGui::SetCursorPos({ 1500, 1500 });
	//ImGui::TextUnformatted("hello");
	
	{
		if (true == ImGui::Button("Data Save Test"))
		{
			UEngineDirectory Dir;
			Dir.MoveToSearchChild("Config");
			Dir.Move("TileMapData");

			std::vector<std::vector<int>> TileData = { {4,3, 2}, {5,6, 7}, {7,6, 7} };

			UEngineSerializer Ser;
			Ser << TileData;

			UEngineFile File = Dir.GetPathFromFile("SaveData.Data");
			File.Open(EIOOpenMode::Write, EIODataType::Binary);
			File.Save(Ser);
		}

		if (true == ImGui::Button("Data Load Test"))
		{
			UEngineDirectory Dir;
			Dir.MoveToSearchChild("Config");
			Dir.Move("TileMapData");

			std::vector<std::vector<int>> TileData;
			UEngineSerializer Ser;

			UEngineFile File = Dir.GetPathFromFile("SaveData.Data");
			File.Open(EIOOpenMode::Read, EIODataType::Binary);
			File.Load(Ser);

			Ser >> TileData;

			int a = 0;
		}
	}

	ImGui::EndChild();
}

//bool MapEditorGUI::FileExists(const wchar_t* _FileName)
//{
//	return PathFileExists(_FileName) != false;
//}

//void MapEditorGUI::CreateXmlFile(const wchar_t* _FileName)
//{
//	IStream* pFileStream = nullptr;
//	HRESULT hr = SHCreateStreamOnFileW(_FileName, STGM_READ, &pFileStream);
//
//	//IXmlWriter* pWirter;
//
//	if (FAILED(hr))
//	{
//		MsgBoxAssert("Failed to create file stream: " + hr);
//		//std::cerr << "Failed to create file stream: " << hr << std::endl;
//		return;
//	}
//
//	//IXmlReader* pReader;
//	//IXmlWriter* pWriter;
//	//hr = CreateXmlWriter(__uuidof(IXmlWriter), (void**)&pWriter, nullptr); // Error
//	//if (FAILED(hr))
//	//{
//	//	MsgBoxAssert("Failed to create XML reader: : " + hr);
//	//	//std::cerr << "Failed to create XML reader: " << hr << std::endl;
//	//	pFileStream->Release();
//	//	return;
//	//}
//}

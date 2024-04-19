#include "PreCompile.h"
#include "MapEditorGUI.h"
#include "TileMapLevel.h"
#include <EngineCore/TileRenderer.h>
#include "TileMap.h"
#include <EngineCore/Camera.h>

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


	ImGui::InputFloat2("TileSize", &InputTileSize.X); // ��������Ʈ Ÿ���� Size�� �����´�.
	ImGui::InputInt2("Height and Width", InputHWValue);
	ImGui::InputText("Data File Name", name, IM_ARRAYSIZE(name));

	std::string FileName(name);
	FileName += ".png";

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
			else if (InputHWValue[0] == 0 || InputHWValue[1] == 0)
			{
				IsCreateImage = false;
			}
			//else if (5 > FileName.size())
			//{
			//	IsCreateImage = false;
			//}
			else
			{
				TileRenderer->CreateTileMap("Map4X(64).png", { InputTileSize.X, InputTileSize.Y }, InputHWValue[0], InputHWValue[1], 0);
				//TileRenderer->CreateTileMap(FileName, { InputTileSize.X, InputTileSize.Y }, InputHWValue[0], InputHWValue[1], 0);
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

	// Save (�� ������ ����)
	{
		if (true == ImGui::Button("Data Save"))
		{
			std::vector<std::vector<int>> TileData = TileRenderer->GetTileMapData();

			if (0 == TileData.size())
			{
				// ���� ������ �ʾ���.
			}
			else
			{
				UEngineDirectory Dir;
				Dir.MoveToSearchChild("Config");
				Dir.Move("TileMapData");

				//std::vector<std::vector<int>> TileData_Test = { {4,3, 2}, {5,6, 7}, {7,6, 7} };

				UEngineSerializer Ser;
				std::string FileName = "DarkDesert_Sprite.png";
				Ser << FileName;
				Ser << TileData;

				UEngineFile File = Dir.GetPathFromFile("SaveData.Data");
				File.Open(EIOOpenMode::Write, EIODataType::Binary);
				File.Save(Ser);
			}
		}
	}

	// Save Data To Create
	{ 
		if (true == ImGui::Button("DataToCreate"))
		{
			// File Load
			UEngineDirectory Dir;
			Dir.MoveToSearchChild("Config");
			Dir.Move("TileMapData");

			std::vector<std::vector<int>> TileData;
			std::string FileName = "";
			UEngineSerializer Ser;

			UEngineFile File = Dir.GetPathFromFile("SaveData.Data");
			File.Open(EIOOpenMode::Read, EIODataType::Binary);
			File.Load(Ser);

			Ser >> FileName;
			Ser >> TileData; // ������ �����͸� ����.
			
			// ������ �����͸� ������� �׸���.
			
			size_t ImageXSize = TileData[0].size();
			size_t ImageYSize = TileData.size();

			TileRenderer->CreateTileMap("Map4X(64).png", { 64, 64 }, static_cast<int>(TileData[0].size()), static_cast<int>(TileData.size()), 0);


			int a = 0;
			for (size_t y = 0; y < ImageYSize; y++)
			{
				for (size_t x = 0; x < ImageXSize; x++)
				{
					int ix = static_cast<int>(x);
					int iy = static_cast<int>(y);
					TileRenderer->SetTile(ix, iy, TileData[iy][ix]);
				}
			}
		}
	}

	ImGui::Text(("WorldMouse : " + MousePosWorld.ToString()).c_str());
	float4 Index = TileRenderer->ConvertTileIndex(MousePosWorld);
	ImGui::Text(("TileIndexPos : " + Index.ToString()).c_str());
	ImGui::Text(std::format("Index : {} {}", Index.iX(), Index.iY()).c_str());


	std::shared_ptr<UEngineSprite> Sprite = UEngineSprite::FindRes("Map4X(64).png");
	//std::shared_ptr<UEngineSprite> Sprite = UEngineSprite::FindRes("DarkDesert_Sprite.png");


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
		if (true == ImGui::ImageButton(Text.c_str(), Info.Texture->GetSRV(), { 64, 64 }, UV0, UV1)) // ��� ������.
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
	

	ImGui::EndChild();
}

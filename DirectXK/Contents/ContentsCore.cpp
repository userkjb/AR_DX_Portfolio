#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineEditorGUI.h>
#include <EngineCore/EngineFont.h>

#include "TestGameMode.h"
#include "GameStartGameMode.h"
#include "TitleGameMode.h"
#include "TownGameMode.h"
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
#ifdef _DEBUG
		UEngineEditorGUI::CreateEditorWindow<ContentsGUI>("Contents");
#endif // _DEBUG
		UEngineEditorGUI::CreateEditorWindow<MapEditorGUI>("MapEditor");
	}

	// Text ��� Test
	{
		UEngineFont::Load("�ü�");
	}

	TitleLoadResources();
	TownLoadResources();
	PlayerLoadResources();

	LoadAllImageResources();

	GEngine->CreateLevel<ATestGameMode>("TestGameMode");
	//GEngine->ChangeLevel("PlayLevel");
	//GEngine->CreateLevel<AGameStartGameMode>("GameStartGameMode");
	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<ATownGameMode>("TownLevel");
	GEngine->CreateLevel<ALasleyGameMode>("LasleyLevel");
	GEngine->CreateLevel<ALasleyStageTwoGM>("LasleyLevelTwo");
	GEngine->CreateLevel<ALasleyStageBossGM>("LasleyLevelBoss");

	GEngine->ChangeLevel("TitleLevel");
	//GEngine->ChangeLevel("TownLevel");
}

void UContentsCore::TitleLoadResources()
{
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\TitleLevel");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			// CuttingTest.png texture�ε� ������ �ε尡 �ư�
			// ��������Ʈ�ε� 1��¥���� �ε尡 �� ��Ȳ�̾�.
			UEngineSprite::Load(File.GetFullPath());
		}

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
		Dir.Move("Sound\\Player");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".wav", ".mp3" });
		for (UEngineFile& File : Files)
		{
			File.Open(EIOOpenMode::Read, EIODataType::Binary);

			char Arr[100];
			File.Read(Arr, 100);

			UEngineSound::Load(File.GetFullPath());
		}
	}
}

void UContentsCore::TownLoadResources()
{
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\TownStage");
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
		Dir.Move("Image\\TownStage\\Town");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}
	}
}

void UContentsCore::PlayerLoadResources()
{
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
}

void UContentsCore::LoadAllImageResources()
{
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\MapObject");
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			//std::string Name = Directorys[i].GetFolderName();
			//UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoadFolder(Directorys[i].GetFullPath());
				});
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\UI");
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			//std::string Name = Directorys[i].GetFolderName();
			//UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoadFolder(Directorys[i].GetFullPath());
				});
		}
	}

	// Lasley Game Mode Class
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\LasleyStage");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			// CuttingTest.png texture�ε� ������ �ε尡 �ư�
			// ��������Ʈ�ε� 1��¥���� �ε尡 �� ��Ȳ�̾�.
			//UEngineSprite::Load(File.GetFullPath());
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoad(File.GetFullPath());
				});
		}

		Dir.Move("Boss_Lasley");
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			//std::string Name = Directorys[i].GetFolderName();
			//UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoadFolder(Directorys[i].GetFullPath());
				});
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\LasleyStage");
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			//std::string Name = Directorys[i].GetFolderName();
			//UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoadFolder(Directorys[i].GetFullPath());
				});
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\PlayerActor");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			//UEngineSprite::Load(File.GetFullPath());
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoad(File.GetFullPath());
				});
		}

		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			//std::string Name = Directorys[i].GetFolderName();
			//UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoadFolder(Directorys[i].GetFullPath());
				});
		}
	}

	// test ����
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\Item");
		//std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		//for (UEngineFile& File : Files)
		//{
		//	UEngineSprite::Load(File.GetFullPath());
		//}

		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			//std::string Name = Directorys[i].GetFolderName();
			//UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoadFolder(Directorys[i].GetFullPath());
				});
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\Item\\CosmosSword");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			//UEngineSprite::Load(File.GetFullPath());
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoad(File.GetFullPath());
				});
		}

		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			//std::string Name = Directorys[i].GetFolderName();
			//UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoadFolder(Directorys[i].GetFullPath());
				});
		}
	}

	// ALasleyStageTwoGM

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\LasleyStage\\Stage_Monster");
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			//std::string Name = Directorys[i].GetFolderName();
			//UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoadFolder(Directorys[i].GetFullPath());
				});
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\GlobalMonster\\Skeleton");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			//UEngineSprite::Load(File.GetFullPath());
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoad(File.GetFullPath());
				});
		}
	}

	// Boss
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image\\BossUI");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			//UEngineSprite::Load(File.GetFullPath());
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoad(File.GetFullPath());
				});
		}
	}
}
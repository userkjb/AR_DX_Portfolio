#pragma once
#include <string>
#include <map>
#include <EngineBase/PathObject.h>

/// <summary>
/// ��� Resource���� �ش� Ŭ������ ��� �޴´�.
/// </summary>
/// <typeparam name="ResType"></typeparam>
template<typename ResType>
class UEngineResources : public UPathObject
{
public:
	// constrcuter destructer
	UEngineResources() {}
	~UEngineResources() {}
	
	// delete Function
	UEngineResources(const UEngineResources& _Other) = delete;
	UEngineResources(UEngineResources&& _Other) noexcept = delete;
	UEngineResources& operator=(const UEngineResources& _Other) = delete;
	UEngineResources& operator=(UEngineResources&& _Other) noexcept = delete;

	/// <summary>
	/// Resource ã��.
	/// </summary>
	/// <param name="_Name"></param>
	/// <returns></returns>
	static std::shared_ptr<ResType> FindRes(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		if (false == NameResources.contains(UpperName))
		{
			return nullptr;
		}

		return NameResources[UpperName];
	}

	/// <summary>
	/// Resource ���� ����.
	/// </summary>
	/// <param name="_Name"></param>
	/// <returns></returns>
	static bool IsRes(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);
		return NameResources.contains(UpperName);
	}

	/// <summary>
	/// ��θ� �ִ� Resource ����.
	/// </summary>
	/// <param name="_Path"></param>
	/// <returns></returns>
	static std::shared_ptr<ResType> CreateResName(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		CreateResName(FileName, _Path);
	}

	/// <summary>
	/// �̸�, ��� �� ���� Resource ����
	/// </summary>
	/// <param name="_Name"></param>
	/// <param name="_Path"></param>
	/// <returns></returns>
	static std::shared_ptr<ResType> CreateResName(std::string_view _Name, std::string_view _Path)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		std::shared_ptr<ResType> NewRes = std::make_shared<ResType>();
		NewRes->SetName(_Name);
		NewRes->SetPath(_Path);

		if (true == NameResources.contains(UpperName))
		{
			MsgBoxAssert("�̹� �����ϴ� ���ҽ��� �� �ε��Ϸ��� �߽��ϴ�." + UpperName);
		}

		NameResources[UpperName] = NewRes;
		return NewRes;
	}

	/// <summary>
	/// �̸�, ��� ���� Resource ����.
	/// </summary>
	/// <returns></returns>
	static std::shared_ptr<ResType> CreateResUnName()
	{
		std::shared_ptr<ResType> NewRes = std::make_shared<ResType>();
		UnNameResources.push_back(NewRes);
		return NewRes;
	}

	
	static void ResourcesRelease()
	{
		// Ŭ����������
		// �ƹ��� �̾ȿ� �ִ� ���ҽ����� ���¾ֵ��� ���ٸ�
		// �˾Ƽ� ������ ���̴�.
		UnNameResources.clear();
		NameResources.clear();
	}

protected:

private:
	static std::map<std::string, std::shared_ptr<ResType>> NameResources;
	static std::list<std::shared_ptr<ResType>> UnNameResources;
	// Resource�� ���� �̸��� ��δ� UPathObject�� ������ �ִ�.
};

// ���������� ����� �߰��Ҽ��� ����?
// ���ø��̸� ������ �ذ�˴ϴ�.
// ���ø� static ������ �����ϴ� ����� ����� �Ѵ�.
template<typename ResType>
std::map<std::string, std::shared_ptr<ResType>> UEngineResources<ResType>::NameResources;

// ���ø� static ���� �����ϴ¹�.
template<typename ResType>
std::list<std::shared_ptr<ResType>> UEngineResources<ResType>::UnNameResources;
#pragma once
#include <string>
#include <map>
#include <EngineBase/PathObject.h>

/// <summary>
/// 모든 Resource들은 해당 클래스를 상속 받는다.
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
	/// Resource 찾기.
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
	/// Resource 존재 여부.
	/// </summary>
	/// <param name="_Name"></param>
	/// <returns></returns>
	static bool IsRes(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);
		return NameResources.contains(UpperName);
	}

	/// <summary>
	/// 경로만 있는 Resource 생성.
	/// </summary>
	/// <param name="_Path"></param>
	/// <returns></returns>
	static std::shared_ptr<ResType> CreateResName(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		return CreateResName(FileName, _Path);
	}

	/// <summary>
	/// 이름, 경로 를 가진 Resource 생성
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
			MsgBoxAssert("이미 존재하는 리소스를 또 로드하려고 했습니다." + UpperName);
		}

		NameResources[UpperName] = NewRes;
		return NewRes;
	}

	/// <summary>
	/// 이름, 경로 없는 Resource 생성.
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
		// 클리어했을때
		// 아무도 이안에 있는 리소스들을 쓰는애들이 없다면
		// 알아서 삭제될 것이다.
		UnNameResources.clear();
		NameResources.clear();
	}

protected:

private:
	static std::map<std::string, std::shared_ptr<ResType>> NameResources;
	static std::list<std::shared_ptr<ResType>> UnNameResources;
	// Resource에 대한 이름과 경로는 UPathObject가 가지고 있다.
};

// 전역변수는 헤더에 추가할수가 없죠?
// 템플릿이면 문제가 해결됩니다.
// 템플릿 static 변수를 선언하는 방법을 배워야 한다.
template<typename ResType>
std::map<std::string, std::shared_ptr<ResType>> UEngineResources<ResType>::NameResources;

// 템플릿 static 변수 선언하는법.
template<typename ResType>
std::list<std::shared_ptr<ResType>> UEngineResources<ResType>::UnNameResources;
#pragma once
#include <EnginePlatform/EngineResources.h>
#include "EngineShader.h"

// Ό³Έν :
class UEngineConstantBuffer : public UEngineResources<UEngineConstantBuffer>
{
public:
	// constrcuter destructer
	UEngineConstantBuffer();
	~UEngineConstantBuffer();

	// delete Function
	UEngineConstantBuffer(const UEngineConstantBuffer& _Other) = delete;
	UEngineConstantBuffer(UEngineConstantBuffer&& _Other) noexcept = delete;
	UEngineConstantBuffer& operator=(const UEngineConstantBuffer& _Other) = delete;
	UEngineConstantBuffer& operator=(UEngineConstantBuffer&& _Other) noexcept = delete;

protected:

private:
	static std::map<EShaderType, std::map<std::string, std::map<int, std::shared_ptr<UEngineConstantBuffer>>>> ConstantBuffers;
};


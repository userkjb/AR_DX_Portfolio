#pragma once
#include "EngineEnums.h"

// ���� :
class UEngineShader;
class UEngineShaderResources
{
	friend UEngineShader;

public:

protected:

private:
	void ShaderResourcesCheck(EShaderType _Type, std::string_view _EntryName, ID3DBlob* _ShaderCode);
};
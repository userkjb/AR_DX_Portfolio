#pragma once
#include "EngineEnums.h"

// setter��� �༮�� ��� ���� �̴ϴ�.
class UEngineConstantBufferSetter
{
public:
	std::shared_ptr<class UEngineConstantBuffer> Res;
	// �� ���͸��� ������ �ִ� �����͸� ������ �༮
	void* SettingCPU = nullptr;
};

// ���� :
class UEngineShader;
class UEngineShaderResources
{
	friend UEngineShader;

public:

protected:

private:
	void ShaderResourcesCheck(EShaderType _Type, std::string_view _EntryName, ID3DBlob* _ShaderCode);
	
	// �ȼ����̴��� 
	// ���ؽ� ���̴� 
	std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>> ConstantBuffers;
};
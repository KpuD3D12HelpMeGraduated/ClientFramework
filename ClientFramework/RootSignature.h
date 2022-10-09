#pragma once
#include "Util.h"
class RootSignature
{
public:
	ComPtr<ID3D12RootSignature>	_signature;
	D3D12_STATIC_SAMPLER_DESC _samplerDesc;

	//루트 시그니처 생성
	void CreateRootSignature(shared_ptr<Device> devicePtr);
};
#pragma once
#include "Util.h"
#include "Device.h"
#include "CmdQueue.h"
#include "SwapChain.h"
#include "RTV.h"
#include "VertexBuffer.h"
#include "RootSignature.h"
#include "PSO.h"
#include "ConstantBuffer.h"
#include "DescHeap.h"
#include "IndexBuffer.h"
#include "Texture.h"

class DxEngine {
public:
	//DX엔진 초기화
	void Init(WindowInfo windowInfo);
	
	//매 프레임마다 그리기
	void Draw(shared_ptr<SwapChain> swapChainPtr, shared_ptr<RTV> rtvPtr, shared_ptr<VertexBuffer> vertexBufferPtr, shared_ptr<RootSignature> rootsignaturePtr,
		shared_ptr<PSO> psoPtr, shared_ptr<ConstantBuffer> constantBufferPtr, shared_ptr<DescHeap> descHeapPtr, shared_ptr<IndexBuffer> indexBufferPtr, shared_ptr<Texture> texturePtr);

	//요소별 객체 포인터
	shared_ptr<Device> deviceInst = make_shared<Device>();
	shared_ptr<CmdQueue> cmdQueueInst = make_shared<CmdQueue>();
	shared_ptr<SwapChain> swapChainPtr = make_shared<SwapChain>();
	shared_ptr<RTV> rtvPtr = make_shared<RTV>();
	shared_ptr<VertexBuffer> vertexBufferPtr = make_shared<VertexBuffer>();
	shared_ptr<RootSignature> rootSignaturePtr = make_shared<RootSignature>();
	shared_ptr<PSO> psoPtr = make_shared<PSO>();
	shared_ptr<ConstantBuffer> constantBufferPtr = make_shared<ConstantBuffer>();
	shared_ptr<DescHeap> descHeapPtr = make_shared<DescHeap>();
	shared_ptr<IndexBuffer> indexBufferPtr = make_shared<IndexBuffer>();
	shared_ptr<Texture> texturePtr = make_shared<Texture>();

private:
	//화면 크기 관련
	D3D12_VIEWPORT	_viewport;
	D3D12_RECT		_scissorRect;
};
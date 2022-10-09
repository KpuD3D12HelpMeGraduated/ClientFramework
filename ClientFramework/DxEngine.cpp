#include "DxEngine.h"
#include "Device.h"

void DxEngine::Init(WindowInfo windowInfo)
{
	//화면 크기 설정
	_viewport = { 0, 0, static_cast<FLOAT>(windowInfo.ClientWidth), static_cast<FLOAT>(windowInfo.ClientHeight), 0.0f, 1.0f };
	_scissorRect = CD3DX12_RECT(0, 0, windowInfo.ClientWidth, windowInfo.ClientHeight);

	//DX엔진 초기화
	deviceInst->CreateDevice();
	cmdQueueInst->CreateCmdListAndCmdQueue(deviceInst);
	swapChainPtr->DescriptAndCreateSwapChain(windowInfo, deviceInst, cmdQueueInst);
	rtvPtr->CreateRTV(deviceInst, swapChainPtr);
	rootSignaturePtr->CreateRootSignature(deviceInst);
	constantBufferPtr->CreateConstantBuffer(sizeof(Transform), 256, deviceInst);
	constantBufferPtr->CreateView(deviceInst);
	descHeapPtr->CreateDescTable(256, deviceInst);
}

void DxEngine::Draw(shared_ptr<SwapChain> swapChainPtr, shared_ptr<RTV> rtvPtr, shared_ptr<VertexBuffer> vertexBufferPtr, shared_ptr<RootSignature> rootsignaturePtr,
	shared_ptr<PSO> psoPtr, shared_ptr<ConstantBuffer> constantBufferPtr, shared_ptr<DescHeap> descHeapPtr, shared_ptr<IndexBuffer> indexBufferPtr, shared_ptr<Texture> texturePtr)
{
	//렌더 시작
	cmdQueueInst->_cmdAlloc->Reset();
	cmdQueueInst->_cmdList->Reset(cmdQueueInst->_cmdAlloc.Get(), nullptr);

	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(swapChainPtr->_renderTargets[swapChainPtr->_backBufferIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	cmdQueueInst->_cmdList->SetGraphicsRootSignature(rootsignaturePtr->_signature.Get());
	constantBufferPtr->_currentIndex = 0;
	descHeapPtr->_currentGroupIndex = 0;

	ID3D12DescriptorHeap* descHeap = descHeapPtr->_descHeap.Get();
	cmdQueueInst->_cmdList->SetDescriptorHeaps(1, &descHeap);

	cmdQueueInst->_cmdList->ResourceBarrier(1, &barrier);

	cmdQueueInst->_cmdList->RSSetViewports(1, &_viewport);
	cmdQueueInst->_cmdList->RSSetScissorRects(1, &_scissorRect);

	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = rtvPtr->_rtvHandle[swapChainPtr->_backBufferIndex];
	cmdQueueInst->_cmdList->ClearRenderTargetView(backBufferView, Colors::LightSteelBlue, 0, nullptr);
	cmdQueueInst->_cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, nullptr);

	//렌더
	cmdQueueInst->_cmdList->SetPipelineState(psoPtr->_pipelineState.Get());
	Transform t;
	t.offset = XMFLOAT4(0.25f, 0.f, 0.f, 0.f);
	vertexBufferPtr->_transform = t;
	{
		cmdQueueInst->_cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		cmdQueueInst->_cmdList->IASetVertexBuffers(0, 1, &vertexBufferPtr->_vertexBufferView);
		cmdQueueInst->_cmdList->IASetIndexBuffer(&indexBufferPtr->_indexBufferView);
		{
			D3D12_CPU_DESCRIPTOR_HANDLE handle = constantBufferPtr->PushData(0, &vertexBufferPtr->_transform, sizeof(vertexBufferPtr->_transform));
			descHeapPtr->SetCBV(handle, 0, deviceInst);
			descHeapPtr->SetSRV(texturePtr->_srvHandle, 5, deviceInst);
		}

		descHeapPtr->CommitTable(cmdQueueInst);
		cmdQueueInst->_cmdList->DrawIndexedInstanced(indexBufferPtr->_indexCount, 1, 0, 0, 0);
	}

	//렌더 종료
	D3D12_RESOURCE_BARRIER barrier2 = CD3DX12_RESOURCE_BARRIER::Transition(swapChainPtr->_renderTargets[swapChainPtr->_backBufferIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT); // 화면 출력

	cmdQueueInst->_cmdList->ResourceBarrier(1, &barrier2);
	cmdQueueInst->_cmdList->Close();

	ID3D12CommandList* cmdListArr[] = { cmdQueueInst->_cmdList.Get() };
	cmdQueueInst->_cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	swapChainPtr->_swapChain->Present(0, 0);

	cmdQueueInst->WaitSync();

	swapChainPtr->_backBufferIndex = (swapChainPtr->_backBufferIndex + 1) % SWAP_CHAIN_BUFFER_COUNT;
}
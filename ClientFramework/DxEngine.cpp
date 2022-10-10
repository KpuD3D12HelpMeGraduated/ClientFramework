#include "DxEngine.h"
#include "Device.h"

void DxEngine::Init(WindowInfo windowInfo)
{
	//화면 크기 설정
	_viewport = { 0, 0, static_cast<FLOAT>(windowInfo.ClientWidth), static_cast<FLOAT>(windowInfo.ClientHeight), 0.0f, 1.0f };
	_scissorRect = CD3DX12_RECT(0, 0, windowInfo.ClientWidth, windowInfo.ClientHeight);

	//DX엔진 초기화
	devicePtr->CreateDevice();
	cmdQueuePtr->CreateCmdListAndCmdQueue(devicePtr);
	swapChainPtr->DescriptAndCreateSwapChain(windowInfo, devicePtr, cmdQueuePtr);
	rtvPtr->CreateRTV(devicePtr, swapChainPtr);
	rootSignaturePtr->CreateRootSignature(devicePtr);
	constantBufferPtr->CreateConstantBuffer(sizeof(Transform), 256, devicePtr);
	constantBufferPtr->CreateView(devicePtr);
	descHeapPtr->CreateDescTable(256, devicePtr);
	dsvPtr->CreateDSV(DXGI_FORMAT_D32_FLOAT, windowInfo, devicePtr);
	RECT rect = { 0, 0, windowInfo.ClientWidth, windowInfo.ClientHeight };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(windowInfo.hwnd, 0, 100, 100, windowInfo.ClientWidth, windowInfo.ClientHeight, 0);
	dsvPtr->CreateDSV(DXGI_FORMAT_D32_FLOAT, windowInfo, devicePtr);
}

void DxEngine::Draw()
{
	//렌더 시작
	cmdQueuePtr->_cmdAlloc->Reset();
	cmdQueuePtr->_cmdList->Reset(cmdQueuePtr->_cmdAlloc.Get(), nullptr);

	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(swapChainPtr->_renderTargets[swapChainPtr->_backBufferIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	cmdQueuePtr->_cmdList->SetGraphicsRootSignature(rootSignaturePtr->_signature.Get());
	constantBufferPtr->_currentIndex = 0;
	descHeapPtr->_currentGroupIndex = 0;

	ID3D12DescriptorHeap* descHeap = descHeapPtr->_descHeap.Get();
	cmdQueuePtr->_cmdList->SetDescriptorHeaps(1, &descHeap);

	cmdQueuePtr->_cmdList->ResourceBarrier(1, &barrier);

	cmdQueuePtr->_cmdList->RSSetViewports(1, &_viewport);
	cmdQueuePtr->_cmdList->RSSetScissorRects(1, &_scissorRect);

	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = rtvPtr->_rtvHandle[swapChainPtr->_backBufferIndex];
	cmdQueuePtr->_cmdList->ClearRenderTargetView(backBufferView, Colors::LightSteelBlue, 0, nullptr);
	D3D12_CPU_DESCRIPTOR_HANDLE depthStencilView = dsvPtr->_dsvHandle;
	cmdQueuePtr->_cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, &depthStencilView);

	cmdQueuePtr->_cmdList->ClearDepthStencilView(depthStencilView, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	//렌더
	{
		cmdQueuePtr->_cmdList->SetPipelineState(psoPtr->_pipelineState.Get());
		Transform t;
		t.offset = XMFLOAT4(0.f, 0.f, 0.2f, 0.f);
		vertexBufferPtr->_transform = t;

		cmdQueuePtr->_cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		cmdQueuePtr->_cmdList->IASetVertexBuffers(0, 1, &vertexBufferPtr->_vertexBufferView);
		cmdQueuePtr->_cmdList->IASetIndexBuffer(&indexBufferPtr->_indexBufferView);
		{
			D3D12_CPU_DESCRIPTOR_HANDLE handle = constantBufferPtr->PushData(0, &vertexBufferPtr->_transform, sizeof(vertexBufferPtr->_transform));
			descHeapPtr->SetCBV(handle, 0, devicePtr);
			descHeapPtr->SetSRV(texturePtr->_srvHandle, 5, devicePtr);
		}

		descHeapPtr->CommitTable(cmdQueuePtr);
		cmdQueuePtr->_cmdList->DrawIndexedInstanced(indexBufferPtr->_indexCount, 1, 0, 0, 0);
	}

	//깊이검사가 잘 수행되는지 테스트 해보기 위해 두번째 메쉬 그리기
	{
		Transform t2;
		t2.offset = XMFLOAT4(0.25f, 0.25f, 0.3f, 0.f);
		vertexBufferPtr->_transform = t2;

		cmdQueuePtr->_cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		cmdQueuePtr->_cmdList->IASetVertexBuffers(0, 1, &vertexBufferPtr->_vertexBufferView);
		cmdQueuePtr->_cmdList->IASetIndexBuffer(&indexBufferPtr->_indexBufferView);
		{
			D3D12_CPU_DESCRIPTOR_HANDLE handle2 = constantBufferPtr->PushData(0, &vertexBufferPtr->_transform, sizeof(vertexBufferPtr->_transform));
			descHeapPtr->SetCBV(handle2, 0, devicePtr);
			descHeapPtr->SetSRV(texturePtr->_srvHandle, 5, devicePtr);
		}

		descHeapPtr->CommitTable(cmdQueuePtr);
		cmdQueuePtr->_cmdList->DrawIndexedInstanced(indexBufferPtr->_indexCount, 1, 0, 0, 0);
	}

	//렌더 종료
	D3D12_RESOURCE_BARRIER barrier2 = CD3DX12_RESOURCE_BARRIER::Transition(swapChainPtr->_renderTargets[swapChainPtr->_backBufferIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT); // 화면 출력

	cmdQueuePtr->_cmdList->ResourceBarrier(1, &barrier2);
	cmdQueuePtr->_cmdList->Close();

	ID3D12CommandList* cmdListArr[] = { cmdQueuePtr->_cmdList.Get() };
	cmdQueuePtr->_cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	swapChainPtr->_swapChain->Present(0, 0);

	cmdQueuePtr->WaitSync();

	swapChainPtr->_backBufferIndex = (swapChainPtr->_backBufferIndex + 1) % SWAP_CHAIN_BUFFER_COUNT;
}
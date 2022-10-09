#pragma once
//라이브러리
#include <Windows.h>
#include <tchar.h>

#include <dxgi1_4.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <d3d12.h>
#include "d3dx12.h"
#include <DirectXColors.h>
#include <vector>

#include <string>
#include <filesystem>

#include "DirectXTex.h"
#include "DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\DirectXTex_debug.lib")
#else
#pragma comment(lib, "..\\DirectXTex.lib")
#endif

#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "D3D12.lib")
#pragma comment (lib, "dxgi.lib")

//네임스페이스
using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;
namespace fs = std::filesystem;

#define SWAP_CHAIN_BUFFER_COUNT 2
#define CBV_REGISTER_COUNT 5
#define SRV_REGISTER_COUNT 5
#define REGISTER_COUNT 10

//정점 구조체
struct Vertex
{
	XMFLOAT3 pos;
	XMFLOAT4 color;
	XMFLOAT2 uv;
};

//상수버퍼로 넘겨줄 구조체의 형태(현재는 상수를 통한 이동을 위해 transform)
struct Transform
{
	XMFLOAT4 offset;
};

//윈도우와 관련된 정보
struct WindowInfo {
	HWND hwnd;
	int ClientWidth = 600;
	int ClientHeight = 600;
};
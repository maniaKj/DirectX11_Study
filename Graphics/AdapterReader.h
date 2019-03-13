#pragma once
#include "..\\ErrorLogger.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "DXGI.lib")
#include <wrl/client.h>
#include <vector>

class AdapterData
{
public:
	AdapterData(IDXGIAdapter* pAdapter);
	IDXGIAdapter* pAdapter; // 생성할 장치를 나타내는 디스플레이 어댑터를 지정
	DXGI_ADAPTER_DESC description;
};

class AdapterReader {
public:
	static std::vector<AdapterData> GetAdapters();
private:
	static std::vector<AdapterData> adapters;
};
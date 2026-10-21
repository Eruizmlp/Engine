#include "Globals.h"
#include "ModuleD3D12.h"

ModuleD3D12::ModuleD3D12(HWND hWnd) : hWnd(hWnd)
{
	
}

bool ModuleD3D12::enableDebugLayer()
{
#ifdef _DEBUG
	ComPtr<ID3D12Debug> debugInterface;
	if (FAILED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface))))
	{
		LOG("Failed to get D3D12 debug interface\n");
		return false;
	}

	debugInterface->EnableDebugLayer();
	LOG("D3D12 debug layer enabled\n");
#endif
	return true;
}

bool ModuleD3D12::createFactory()
{
	UINT factoryFlags = 0;
#ifdef _DEBUG
	factoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

	if (FAILED(CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(&factory))))
	{
		LOG("Failed to create DXGI factory\n");
		return false;
	}

	LOG("DXGI factory created\n");
	return true;
}

bool ModuleD3D12::createDevice()
{
	if (FAILED(factory->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter))))
	{
		LOG("Failed to select a high-performance GPU adapter\n");
		return false;
	}

	if (FAILED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device))))
	{
		LOG("Failed to create D3D12 device\n");
		return false;
	}

	LOG("D3D12 device created\n");
	return true;
}

bool ModuleD3D12::setUpInfoQueue()
{
#ifdef _DEBUG
	ComPtr<ID3D12InfoQueue> infoQueue;
	if (FAILED(device.As(&infoQueue)))
	{
		LOG("Failed to get D3D12 info queue\n");
		return false;
	}
	for (const D3D12_MESSAGE_SEVERITY severity : 
		{D3D12_MESSAGE_SEVERITY_CORRUPTION,
		D3D12_MESSAGE_SEVERITY_ERROR,
		D3D12_MESSAGE_SEVERITY_WARNING})
	{	
		if (FAILED(infoQueue->SetBreakOnSeverity(severity, TRUE)))
		{

			LOG("Failed to set break on severity %d\n", static_cast<int>(severity));
			return false;
		}	
	}

#endif
	return true;
}
bool ModuleD3D12::createCommandQueue()
{

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	if(FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue))))
	{
		LOG("Failed to create D3D12 command queue\n\n");
		return false;
	}
	
	LOG("Successfully created D3D12 command queue\n\n");

	return true;
}
bool ModuleD3D12::createSwapChain()
{	

	return true;
}

bool ModuleD3D12::init()
{
	if (!enableDebugLayer())
		return false;

	if (!createFactory())
		return false;

	if (!createDevice())
		return false;

	if (!setUpInfoQueue())
		return false;

	if (!createCommandQueue())
		return false;

	return true;
}

bool ModuleD3D12::cleanUp()
{
	LOG("ModuleD3D12 cleaned up\n");
	return true;
}
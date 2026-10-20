#include "Globals.h"
#include "ModuleD3D12.h"

bool ModuleD3D12::enableDebugLayer()
{
	// Enable the D3D12 debug layer.	
#ifdef _DEBUG
	ComPtr<ID3D12Debug> debugInterface;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface))))
	{
		debugInterface->EnableDebugLayer();
		LOG("D3D12 debug layer enabled\n");
	}
	else
	{
		LOG("Failed to get D3D12 debug interface");
		return false;
	}
#endif 
	return true;

}

bool ModuleD3D12::init()
{	
	if (!enableDebugLayer())
		return false;

	return true;
}

bool ModuleD3D12::cleanUp()
{
	#ifdef _DEBUG
	LOG("ModuleD3D12 cleaned up\n");
	#endif 

	return true;
}
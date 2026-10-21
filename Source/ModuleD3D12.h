#pragma once
#include "Globals.h"
#include "Module.h"

class ModuleD3D12 : public Module
{
public:

	ModuleD3D12(HWND hWnd);

	bool init() override;
	bool cleanUp() override;

	const ComPtr<ID3D12Device5>& getDevice() const { return device; }
	const ComPtr<ID3D12CommandQueue>& getCommandQueue() const { return commandQueue; }

private:
	bool enableDebugLayer();
	bool createFactory();
	bool createDevice();
	bool setUpInfoQueue();
	bool createCommandQueue();
	bool createSwapChain();

	HWND hWnd = nullptr;


	ComPtr<IDXGIFactory6> factory;
	ComPtr<IDXGIAdapter4> adapter;
	ComPtr<ID3D12Device5> device;
	ComPtr<ID3D12CommandQueue> commandQueue;

};
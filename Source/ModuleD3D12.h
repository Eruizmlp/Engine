#pragma once
#include "Globals.h"
#include "Module.h"

class ModuleD3D12 : public Module
{
public:
	bool init() override;
	bool cleanUp() override;

	const ComPtr<ID3D12Device5>& getDevice() const { return device; }

private:
	bool enableDebugLayer();
	bool createFactory();
	bool createDevice();
	bool setUpInfoQueue();

	ComPtr<IDXGIFactory6> factory;
	ComPtr<IDXGIAdapter4> adapter;
	ComPtr<ID3D12Device5> device;
	ComPtr<ID3D12InfoQueue> infoQueue;

};
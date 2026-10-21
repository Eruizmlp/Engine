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

	ComPtr<IDXGIFactory6> factory;
	ComPtr<IDXGIAdapter4> adapter;
	ComPtr<ID3D12Device5> device;
};
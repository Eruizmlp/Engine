#pragma once
#include "Module.h"



class D3D12Module : public Module
{
public:

	bool init() override;
	bool cleanUp() override;
	
private:

};

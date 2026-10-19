#include "Globals.h"
#include "D3D12Module.h"

bool D3D12Module::init()
{
#ifdef _DEBUG
    LOG("Hello, world")
#endif 
    return true;
}

bool D3D12Module::cleanUp()
{
#ifdef _DEBUG
    LOG("Ciaociaociao")
#endif
    return true;

}



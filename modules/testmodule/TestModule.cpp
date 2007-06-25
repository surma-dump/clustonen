#include "TestModule.h"

/**
 * Standard Constructor
 */
TestModule::TestModule()
{
}

/**
 * Destructor
 */
TestModule::~TestModule() 
{
}

const char* TestModule::getName()
{
	return "TestModule" ;
}

int TestModule::getHookPosition()
{
	return MODULE_LOADING_REQUEST ;
}

int TestModule::processEvent (ClustonenEvent& event)
{
	return CHAIN_PROCEED ;
}

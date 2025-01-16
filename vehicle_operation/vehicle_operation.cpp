#include <iostream>
#include <vehicle_operation.hpp>

/*******************************************************************************
 *                          Context Specific Definitions
 *******************************************************************************/
/** private definitions*/
void AppVehicleOperation::EntryPoint(void)
{
    std::cout << "AppVehicleOperation EntryPoint" << std::endl;
    Transition(eSleepingIdx);
}

/** public definitions*/
AppVehicleOperation::AppVehicleOperation() : StateChart(mStateNodes, mEventBuffer)
{
    std::cout << "AppVehicleOperation Constructor" << std::endl;
}

void AppVehicleOperation::Initialize()
{
    mAutoDrvShallowHistory = eCruisingIdx;
    // do what ever here to initialize AppVehicleOperation
    EntryPoint();
    StateChart::Initialize();
    std::cout << "AppVehicleOperation Initializer" << std::endl;
}

void AppVehicleOperation::PrintAppVehicleOperation()
{
    std::cout << "Application context, AppVehicleOperation, handled" << std::endl;
}

AppVehicleOperation::~AppVehicleOperation()
{
    std::cout << "AppVehicleOperation Destructor" << std::endl;
}
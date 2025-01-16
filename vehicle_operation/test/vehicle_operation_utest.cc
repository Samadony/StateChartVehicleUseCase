/*
 * vehicle_operation_utest.cc
 *
 *  Created on: Jan 10, 2025
 *      Author: Ahmed Elsamadony
 * 
 * This file contains an example of the unit test for the vehicle_operation statechart.
 * The test is based on the statechart defined in vehicle_operation.hpp
 * 
 * IMPORTANT!
 *  - Not all states were tested, for conclusive test cases of all possible tests please refer
 *    to the original implementation of the statechart.
 *  - The test cases abuses TEST_P, and this is not an optimal way to do your tests, but it is
 *    fast and easy to implementation to validate your statecharts transitions.
 */
#include <vector>
#include <unordered_map>

#include <gtest/gtest.h>

#include "vehicle_operation.hpp"
#include "vehicle_operation_states.hpp"
namespace 
{

static std::vector<state_chart::Signal> const appVehicleOperationEvents = 
{
    AppVehicleOperation::eIgnitionOnEvent,
    AppVehicleOperation::eIgnitionOffEvent,
    AppVehicleOperation::eAutonomousDrivingOnEvent,
    AppVehicleOperation::eAutonomousDrivingOffEvent,
    AppVehicleOperation::eAutomaticParkingOnEvent,
    AppVehicleOperation::eAutomaticParkingOffEvent,
    AppVehicleOperation::eObstacleDetectionEvent,
    AppVehicleOperation::eObstacleClearedEvent,
    AppVehicleOperation::eBusyLaneEvent,
    AppVehicleOperation::eClearLaneEvent,
    AppVehicleOperation::eParkingSpotFoundEvent,
    AppVehicleOperation::eParkingSuccessfulEvent,
    AppVehicleOperation::eParkingActionTimeoutEvent
};

class AppVehicleOperationFixture: public ::testing::TestWithParam<state_chart::Signal>
{
protected:
    AppVehicleOperationFixture() = default;
    ~AppVehicleOperationFixture() override = default;
    void SetUp() override
    {
        appVehicleOperation.Initialize();
    }
    void TearDown() override {}
    AppVehicleOperation appVehicleOperation;
};

// TODO: Add ASCII Drawing
TEST_P(AppVehicleOperationFixture, SleepingStateTransitions) 
{
    state_chart::Signal signal = GetParam();
    static const std::unordered_map<state_chart::Signal, uint8_t> evtToStateMap = 
    {
        {AppVehicleOperation::eIgnitionOnEvent,             AppVehicleOperation::eManualDrivingIdx},
        {AppVehicleOperation::eIgnitionOffEvent,            AppVehicleOperation::eSleepingIdx},
        {AppVehicleOperation::eAutonomousDrivingOnEvent,    AppVehicleOperation::eSleepingIdx},
        {AppVehicleOperation::eAutonomousDrivingOffEvent,   AppVehicleOperation::eSleepingIdx},
        {AppVehicleOperation::eAutomaticParkingOnEvent,     AppVehicleOperation::eSleepingIdx},
        {AppVehicleOperation::eAutomaticParkingOffEvent,    AppVehicleOperation::eSleepingIdx},
        {AppVehicleOperation::eObstacleDetectionEvent,      AppVehicleOperation::eSleepingIdx},
        {AppVehicleOperation::eObstacleClearedEvent,        AppVehicleOperation::eSleepingIdx},
        {AppVehicleOperation::eBusyLaneEvent,               AppVehicleOperation::eSleepingIdx},
        {AppVehicleOperation::eClearLaneEvent,              AppVehicleOperation::eSleepingIdx},
        {AppVehicleOperation::eParkingSpotFoundEvent,       AppVehicleOperation::eSleepingIdx},
        {AppVehicleOperation::eParkingSuccessfulEvent,      AppVehicleOperation::eSleepingIdx},
        {AppVehicleOperation::eParkingActionTimeoutEvent,   AppVehicleOperation::eSleepingIdx}
    };
    state_chart::Event event = {signal};
    appVehicleOperation.SetEvent(event);
    EXPECT_EQ(evtToStateMap.at(event.signal), appVehicleOperation.mCurrentStateIdx);
}

INSTANTIATE_TEST_SUITE_P(SleepingStateTransitions,
                         AppVehicleOperationFixture,
                         testing::ValuesIn(appVehicleOperationEvents));


// TODO: Add ASCII Drawing
TEST_P(AppVehicleOperationFixture, ManualDrivingStateTransition) 
{
    state_chart::Signal signal = GetParam();
    static const std::unordered_map<state_chart::Signal, uint8_t> evtToStateMap = 
    {
        {AppVehicleOperation::eIgnitionOnEvent,             AppVehicleOperation::eManualDrivingIdx},
        {AppVehicleOperation::eIgnitionOffEvent,            AppVehicleOperation::eSleepingIdx},
        {AppVehicleOperation::eAutonomousDrivingOnEvent,    AppVehicleOperation::eCruisingIdx},
        {AppVehicleOperation::eAutonomousDrivingOffEvent,   AppVehicleOperation::eManualDrivingIdx},
        {AppVehicleOperation::eAutomaticParkingOnEvent,     AppVehicleOperation::eSpotSearchingIdx},
        {AppVehicleOperation::eAutomaticParkingOffEvent,    AppVehicleOperation::eManualDrivingIdx},
        {AppVehicleOperation::eObstacleDetectionEvent,      AppVehicleOperation::eManualDrivingIdx},
        {AppVehicleOperation::eObstacleClearedEvent,        AppVehicleOperation::eManualDrivingIdx},
        {AppVehicleOperation::eBusyLaneEvent,               AppVehicleOperation::eManualDrivingIdx},
        {AppVehicleOperation::eClearLaneEvent,              AppVehicleOperation::eManualDrivingIdx},
        {AppVehicleOperation::eParkingSpotFoundEvent,       AppVehicleOperation::eManualDrivingIdx},
        {AppVehicleOperation::eParkingSuccessfulEvent,      AppVehicleOperation::eManualDrivingIdx},
        {AppVehicleOperation::eParkingActionTimeoutEvent,   AppVehicleOperation::eManualDrivingIdx}
    };
    state_chart::Event event = {AppVehicleOperation::eIgnitionOnEvent};
    // Move the StateMachine into ManualDriving state first
    appVehicleOperation.SetEvent(event);
    // Apply parameters to ManualDriving state
    event = {signal};
    appVehicleOperation.SetEvent(event);
    EXPECT_EQ(evtToStateMap.at(event.signal), appVehicleOperation.mCurrentStateIdx);
}

INSTANTIATE_TEST_SUITE_P(ManualDrivingStateTransition,
                         AppVehicleOperationFixture,
                         testing::ValuesIn(appVehicleOperationEvents));
                         
// TODO: Add ASCII Drawing
TEST_P(AppVehicleOperationFixture, CruisingStateTransition) 
{
    state_chart::Signal signal = GetParam();
    static const std::unordered_map<state_chart::Signal, uint8_t> evtToStateMap = 
    {
        {AppVehicleOperation::eIgnitionOnEvent,             AppVehicleOperation::eCruisingIdx},
        {AppVehicleOperation::eIgnitionOffEvent,            AppVehicleOperation::eCruisingIdx},
        {AppVehicleOperation::eAutonomousDrivingOnEvent,    AppVehicleOperation::eCruisingIdx},
        {AppVehicleOperation::eAutonomousDrivingOffEvent,   AppVehicleOperation::eManualDrivingIdx},
        {AppVehicleOperation::eAutomaticParkingOnEvent,     AppVehicleOperation::eCruisingIdx},
        {AppVehicleOperation::eAutomaticParkingOffEvent,    AppVehicleOperation::eCruisingIdx},
        {AppVehicleOperation::eObstacleDetectionEvent,      AppVehicleOperation::eEmergHandlingIdx},
        {AppVehicleOperation::eObstacleClearedEvent,        AppVehicleOperation::eCruisingIdx},
        {AppVehicleOperation::eBusyLaneEvent,               AppVehicleOperation::eOvertakingIdx},
        {AppVehicleOperation::eClearLaneEvent,              AppVehicleOperation::eCruisingIdx},
        {AppVehicleOperation::eParkingSpotFoundEvent,       AppVehicleOperation::eCruisingIdx},
        {AppVehicleOperation::eParkingSuccessfulEvent,      AppVehicleOperation::eCruisingIdx},
        {AppVehicleOperation::eParkingActionTimeoutEvent,   AppVehicleOperation::eCruisingIdx}
    };
    
    // Move the StateMachine into Cruising state first
    appVehicleOperation.SetEvent({AppVehicleOperation::eIgnitionOnEvent});    // from sleeping into ManualDriving
    ASSERT_EQ(AppVehicleOperation::eManualDrivingIdx, appVehicleOperation.mCurrentStateIdx);
    appVehicleOperation.SetEvent({AppVehicleOperation::eAutonomousDrivingOnEvent});    // from ManualDriving into (AutoDriving), consequently Cruising
    ASSERT_EQ(AppVehicleOperation::eCruisingIdx, appVehicleOperation.mCurrentStateIdx);
    // Apply parameters to ManualDriving state
    appVehicleOperation.SetEvent({signal});
    ASSERT_EQ(evtToStateMap.at(signal), appVehicleOperation.mCurrentStateIdx);
}

INSTANTIATE_TEST_SUITE_P(CruisingStateTransition,
                         AppVehicleOperationFixture,
                         testing::ValuesIn(appVehicleOperationEvents));
}  // namespace

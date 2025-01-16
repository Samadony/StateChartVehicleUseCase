
#include <iostream>

#include <vehicle_operation_states.hpp>
#include <vehicle_operation.hpp>

using namespace state_chart;

/*******************************************************************************
 *                              States definitions
 *******************************************************************************/
/*******************************************************************************
 *                               Root (Top State)
 *******************************************************************************/
void Root::Enter(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Root: Entry Action" << std::endl;
}

void Root::Initial(void *const appVehicleOperation)
{
    std::cout << "Root: Initial Action: Transition into Sleeping" << std::endl;
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eSleepingIdx);
}

void Root::Exit(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Root: Exit Action" << std::endl;
}

void Root::PreHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Root: Pre-Hook Action" << std::endl;
}

void Root::PostHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Root: Post-Hook Action" << std::endl;
}

// Event Action
void Root::HandleIgnitionOn(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Ignition On Handled" << std::endl;
}

void Root::HandleIgnitionOff(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Ignition Off Handled" << std::endl;
}

void Root::HandleAutoCmdOn(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Auto Cmd On Handled" << std::endl;
}

void Root::HandleAutoCmdOff(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Auto Cmd Off Handled" << std::endl;
}

void Root::HandleParkingCmdOn(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Parking Cmd On Handled" << std::endl;
}

void Root::HandleParkingCmdOff(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Parking Cmd Off Handled" << std::endl;
}

void Root::HandleObstacleDetected(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Obstacle Detected Handled" << std::endl;
}

void Root::HandleObstacleCleared(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Obstacle Cleared Handled" << std::endl;
}

void Root::HandleClearLane(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Clear Lane Detection Event Handled" << std::endl;
}

void Root::HandleBusyLane(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Busy Lane Detection Event Handled" << std::endl;
}

void Root::HandleSpotFound(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Parking Spot Found Handled" << std::endl;
}

void Root::HandleManeuverSuccessful(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Parking Maneuver Successful Handled" << std::endl;
}

void Root::HandleParkingActionTimeout(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Parking Action Timeout Handled" << std::endl;
}

void Root::HandleDefault(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    std::cout << "Root: Handle default (handling any other unnamed events)" << std::endl;
}

// Event Demultiplexer Interface 
void Root::HandleEvent(void *const appVehicleOperation, Event const *const event)
{
    switch(event->signal)
    {
        case AppVehicleOperation::eIgnitionOnEvent:
            this->HandleIgnitionOn(appVehicleOperation, event);
            break;
        case AppVehicleOperation::eIgnitionOffEvent:
            this->HandleIgnitionOff(appVehicleOperation, event);
            break;
        case AppVehicleOperation::eAutonomousDrivingOnEvent:
            this->HandleAutoCmdOn(appVehicleOperation, event);
            break;
        case AppVehicleOperation::eAutonomousDrivingOffEvent:
            this->HandleAutoCmdOff(appVehicleOperation, event);
            break;
        case AppVehicleOperation::eAutomaticParkingOnEvent:
            this->HandleParkingCmdOn(appVehicleOperation, event);
            break;
        case AppVehicleOperation::eAutomaticParkingOffEvent:
            this->HandleParkingCmdOff(appVehicleOperation, event);
            break;
        case AppVehicleOperation::eObstacleDetectionEvent:
            this->HandleObstacleDetected(appVehicleOperation, event);
            break;
        case AppVehicleOperation::eObstacleClearedEvent:
            this->HandleObstacleCleared(appVehicleOperation, event);
            break;
        case AppVehicleOperation::eBusyLaneEvent:
            this->HandleBusyLane(appVehicleOperation, event);
            break;
        case AppVehicleOperation::eClearLaneEvent:
            this->HandleClearLane(appVehicleOperation, event);
            break;
        case AppVehicleOperation::eParkingSpotFoundEvent:
            this->HandleSpotFound(appVehicleOperation, event);
            break;
        case AppVehicleOperation::eParkingSuccessfulEvent:
            this->HandleManeuverSuccessful(appVehicleOperation, event);
            break;
        case AppVehicleOperation::eParkingActionTimeoutEvent:
            this->HandleParkingActionTimeout(appVehicleOperation, event);
            break;
        default:
            this->HandleDefault(appVehicleOperation, event);
        break;
    }
}

/*******************************************************************************
 *                                Sleeping
 *******************************************************************************/
/** Protected Methods */
void Sleeping::Enter(void *const appVehicleOperation)
{
    std::cout << "Sleeping: Entry Action" << std::endl;
    (void)appVehicleOperation;
}

void Sleeping::Initial(void *const appVehicleOperation)
{
    std::cout << "Sleeping: Initial Action, you can not transition deeper, it is a leaf state ;)" << std::endl;
    (void)appVehicleOperation;
}

void Sleeping::Exit(void *const appVehicleOperation)
{   
    (void)appVehicleOperation;
    std::cout << "Sleeping: Exit Action" << std::endl;
}

void Sleeping::PreHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Sleeping: Pre-Hook Action" << std::endl;
}

void Sleeping::PostHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Sleeping: Post-Hook Action" << std::endl;
}

void Sleeping::HandleIgnitionOn(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eOperatingIdx);
    std::cout << "Sleeping:" << std::endl 
              << "Ignition On Event! Transitioning to Operating" << std::endl
              << "Ignition On Event Handled" << std::endl;
}

/*******************************************************************************
 *                                   Operating
 *******************************************************************************/
void Operating::Enter(void *const appVehicleOperation)
{
    std::cout << "Operating: Entry Action" << std::endl;
    (void)appVehicleOperation;
}

void Operating::Initial(void *const appVehicleOperation)
{
    std::cout << "Operating: Initial Action: Transition to ManualDriving" << std::endl;
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eManualDrivingIdx);
}

void Operating::Exit(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Operating: Exit Action" << std::endl;
}

void Operating::PreHook(void *const appVehicleOperation)
{
    std::cout << "Operating: Pre-Hook Action" << std::endl;
    (void)appVehicleOperation;
}

void Operating::PostHook(void *const appVehicleOperation)
{
    std::cout << "Operating: Post-Hook Action" << std::endl;
    (void)appVehicleOperation;
}

void Operating::HandleObstacleDetected(void *const appVehicleOperation, Event const *const event)
{
    (void)event;
    (void)appVehicleOperation;
    std::cout << "Operating: " << std::endl 
              << "Obstacle Detected Signal! Turning ON obstacle indicator on the dashboard" << std::endl
              << "Obstacle Detected Event Handled" << std::endl;

}

void Operating::HandleObstacleCleared(void *const appVehicleOperation, Event const *const event)
{
    (void)event;
    (void)appVehicleOperation;
    std::cout << "Operating: " << std::endl 
              << "Obstacle Cleared! Turning OFF obstacle indicator on the dashboard" << std::endl
              << "Obstacle Cleared Event Handled" << std::endl;

}

void Operating::HandleClearLane(void *const appVehicleOperation, Event const *const event)
{
    (void)event;
    (void)appVehicleOperation;
    std::cout << "Operating: " << std::endl 
              << "Clear Lane Signal! Lit up Lane indicator with GREEN in the dashboard" << std::endl
              << "Clear Lane Event Handled" << std::endl;

}

void Operating::HandleBusyLane(void *const appVehicleOperation, Event const *const event)
{
    (void)event;
    (void)appVehicleOperation;
    std::cout << "Operating: " << std::endl 
              << "Busy Lane Signal! Lit up Lane indicator with YELLOW in the dashboard" << std::endl
              << "Clear Lane Event Handled" << std::endl;

}

/*******************************************************************************
 *                               ManualDriving
 *******************************************************************************/
/** Protected Methods */
void ManualDriving::Enter(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "ManualDriving: Entry Action" << std::endl;
}

void ManualDriving::Initial(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "ManualDriving: Initial Action, you can not transition deeper, it is a leaf state ;)" << std::endl;
}

void ManualDriving::Exit(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "ManualDriving: Exit Action" << std::endl;
}
void ManualDriving::PreHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "ManualDriving: Pre-Hook Action" << std::endl;
}

void ManualDriving::PostHook(void *const appVehicleOperation)
{
   (void)appVehicleOperation;
    std::cout << "ManualDriving: Post-Hook Action" << std::endl;
}


void ManualDriving::HandleIgnitionOff(void *const appVehicleOperation, Event const *const event)
{
    (void)event;
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eSleepingIdx);
    std::cout << "ManualDriving:" << std::endl 
              << "Ignition Off Signal Detected! Transitioning to Sleeping" << std::endl
              << "Ignition Off Event Handled" << std::endl;
}

void ManualDriving::HandleAutoCmdOn(void *const appVehicleOperation, Event const *const event)
{
    (void)event;
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eAutoDrivingIdx);
    std::cout << "ManualDriving:" << std::endl 
              << "Auto Cmd On Detected! Transitioning to AutoDriving" << std::endl
              << "Auto Cmd On Event Handled" << std::endl;
}

void ManualDriving::HandleParkingCmdOn(void *const appVehicleOperation, Event const *const event)
{
    (void)event;
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eAutoParkingIdx);
    std::cout << "ManualDriving:" << std::endl 
              << "Parking Cmd On Detected! Transitioning to AutoParking" << std::endl
              << "Parking Cmd On Event Handled" << std::endl;
}

/*******************************************************************************
 *                               AutoDriving
 *******************************************************************************/
void AutoDriving::Enter(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "AutoDriving: Entry Action" << std::endl;
}

void AutoDriving::Initial(void *const appVehicleOperation)
{
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eCruisingIdx);
    std::cout << "AutoDriving: Initial Action: Transition to substate Cruising" << std::endl;
}

void AutoDriving::Exit(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "AutoDriving: Exit Action" << std::endl;
}
void AutoDriving::PreHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "AutoDriving: Pre-Hook Action" << std::endl;
}

void AutoDriving::PostHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "AutoDriving: Post-Hook Action" << std::endl;
}

void AutoDriving::HandleAutoCmdOff(void *const appVehicleOperation, Event const *const event)
{
    (void)event;
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eManualDrivingIdx);
    std::cout << "AutoDriving:" << std::endl 
              << "Auto Cmd Off Detected! Transitioning to Manual Driving" << std::endl
              << "Auto Cmd Off Event Handled" << std::endl;
}

/*******************************************************************************
 *                               AutoParking
 *******************************************************************************/
/** Protected Methods */
void AutoParking::Enter(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "AutoParking: Entry Action" << std::endl;
}

void AutoParking::Initial(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eSpotSearchingIdx);
    std::cout << "AutoParking: Initial Action" << std::endl;
}

void AutoParking::Exit(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "AutoParking: Exit Action" << std::endl;
}

void AutoParking::PreHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "AutoParking: Pre-Hook Action" << std::endl;
}

void AutoParking::PostHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "AutoParking: Post-Hook Action" << std::endl;
}

void AutoParking::HandleParkingCmdOn(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    // even if in SpotSearching state, restart it, meaning the driving does not like the spot
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eSpotSearchingIdx);
    std::cout << "AutoParking: " << std::endl 
              << "Restarting the parking process" << std::endl
              << "Parking Cmd On Event Handled" << std::endl;
}

void AutoParking::HandleObstacleDetected(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eSpotSearchingIdx);
    std::cout << "AutoParking: " << std::endl 
              << "Obstacle Detected! Restarting the parking process" << std::endl
              << "Obstacle Detected Event Handled" << std::endl;
}

void AutoParking::HandleParkingActionTimeout(void *const appVehicleOperation, Event const *const event)
{
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eManualDrivingIdx);
    (void)event;

    std::cout << "AutoParking: " << std::endl 
              << "Parking Timeout! Switching to manual mode" << std::endl
              << "Parking Timeout Event Handled" << std::endl;
}

void AutoParking::HandleParkingCmdOff(void *const appVehicleOperation, Event const *const event)
{
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eManualDrivingIdx);
    (void)event;
    std::cout << "AutoParking: " << std::endl 
              << "Parking command is tunred off! Switching to manual mode" << std::endl
              << "Parking Cmd Off Event Handled" << std::endl;
}

/*******************************************************************************
 *                                 Cruising
 *******************************************************************************/
void Cruising::Enter(void *const appVehicleOperation)
{
    // save the current state in the shallow history, you can also use mCurrentStateIdx
    static_cast<AppVehicleOperation*>(appVehicleOperation)->mAutoDrvShallowHistory = AppVehicleOperation::eCruisingIdx;
    std::cout << "Cruising: Entry Action: " << "updating shallow history" << std::endl;
}

void Cruising::Initial(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Cruising: Initial Action, you can not transition deeper, it is a leaf state ;)" << std::endl;
}

void Cruising::Exit(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Cruising: Exit Action" << std::endl;
}

void Cruising::PreHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Cruising: Pre-Hook Action" << std::endl;
}

void Cruising::PostHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Cruising: Post-Hook Action" << std::endl;
}
    

void Cruising::HandleBusyLane(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    Operating::HandleBusyLane(appVehicleOperation, event);
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eOvertakingIdx);
    std::cout << "Cruising: " << std::endl
              << "Busy Lane Detected! Switching to Overtaking" << std::endl 
              << "Busy Lane Event Handled" << std::endl;
}

void Cruising::HandleObstacleDetected(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    Operating::HandleObstacleDetected(appVehicleOperation, event);
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eEmergHandlingIdx);
    std::cout << "Cruising: " << std::endl
              << "Obstacle Detected! Switching to EmergHandling" << std::endl 
              << "Obstacle Detected Event Handled" << std::endl;
}

/*******************************************************************************
 *                                 Overtaking
 *******************************************************************************/
void Overtaking::Enter(void *const appVehicleOperation)
{
    // save the current state in the shallow history, you can also use mCurrentStateIdx
    static_cast<AppVehicleOperation*>(appVehicleOperation)->mAutoDrvShallowHistory = AppVehicleOperation::eOvertakingIdx;
    std::cout << "Overtaking: Entry Action, Save current state in shallow history" << std::endl;
}

void Overtaking::Initial(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Overtaking: Initial Action, No Transition, it is a leaf state/Node :D" << std::endl;
}

void Overtaking::Exit(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Overtaking: Exit Action" << std::endl;
}

void Overtaking::PreHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Overtaking: Pre-Hook Action" << std::endl;
}

void Overtaking::PostHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Overtaking: Post-Hook Action" << std::endl;
}
    

void Overtaking::HandleClearLane(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    Operating::HandleClearLane(appVehicleOperation, event);
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eCruisingIdx);
    std::cout << "Overtaking:" << std::endl 
                << "Clear Lane Signal! Transitioning to Cruising" << std::endl
                << "Clear Lane Event Handled" << std::endl;
}

void Overtaking::HandleObstacleDetected(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    Operating::HandleObstacleDetected(appVehicleOperation, event);
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eEmergHandlingIdx);
    std::cout << "Overtaking:" << std::endl 
              << "Obstacle Detected Signal! Transitioning to EmergHandling State" << std::endl
              << "Obstacle Detected Event Handled" << std::endl;
}

/*******************************************************************************
 *                                 EmergHandling
 *******************************************************************************/
void EmergHandling::Enter(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "EmergHandling: Entry Action" << std::endl;
}

void EmergHandling::Initial(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "EmergHandling: Initial Action, No transition action, it is a leaf node/state" << std::endl;
}

void EmergHandling::Exit(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "EmergHandling: Exit Action" << std::endl;
}

void EmergHandling::PreHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "EmergHandling: Pre-Hook Action" << std::endl;
}

void EmergHandling::PostHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "EmergHandling: Post-Hook Action" << std::endl;
}

void EmergHandling::HandleObstacleCleared(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    Operating::HandleObstacleCleared(appVehicleOperation, event);
    // Go to the previous state (neighbor Node in the tree, hence the usage of a "shallow" history)
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(static_cast<AppVehicleOperation*>(
                                                                                appVehicleOperation)->mAutoDrvShallowHistory);
    std::cout << "EmergHandling:" << std::endl 
              << "Obstacle Cleared Event! Transitioning to the last active state" << std::endl
              << "Obstacle Cleared Event Handled" << std::endl;
}

/*******************************************************************************
 *                                 SpotSearching
 *******************************************************************************/
void SpotSearching::Enter(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "SpotSearching: Entry Action" << std::endl;
}

void SpotSearching::Initial(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "SpotSearching: Initial Action, no transition possible, it is a leaf (atomic) state" << std::endl;
}

void SpotSearching::Exit(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "SpotSearching: Exit Action" << std::endl;
}

void SpotSearching::PreHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "SpotSearching: Pre-Hook Action" << std::endl;
}

void SpotSearching::PostHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "SpotSearching: Post-Hook Action" << std::endl;
}

void SpotSearching::HandleSpotFound(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eManeuveringIdx);
    std::cout << "SpotSearching:" << std::endl 
              << "Parking Spot Found Event! Transitioning to Maneuvering" << std::endl
              << "Parking Spot Found Event Handled" << std::endl;
}

/*******************************************************************************
 *                                 Maneuvering
 *******************************************************************************/
void Maneuvering::Enter(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Maneuvering: Entry Action" << std::endl;
}

void Maneuvering::Initial(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Maneuvering: Initial Action, no deeper transitions are possible (leaf state)" << std::endl;
}

void Maneuvering::Exit(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Maneuvering: Exit Action" << std::endl;
}

void Maneuvering::PreHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Maneuvering: Pre-Hook Action" << std::endl;
}

void Maneuvering::PostHook(void *const appVehicleOperation)
{
    (void)appVehicleOperation;
    std::cout << "Maneuvering: Post-Hook Action" << std::endl;
}

void Maneuvering::HandleManeuverSuccessful(void *const appVehicleOperation, Event const *const event)
{
    (void)appVehicleOperation;
    (void)event;
    static_cast<AppVehicleOperation*>(appVehicleOperation)->Transition(AppVehicleOperation::eManualDrivingIdx);
    std::cout << "Maneuvering:" << std::endl 
              << "Maneuvering Successful Event! Transitioning to ManualDriving" << std::endl
              << "Maneuvering Successful Event Handled" << std::endl;
}

/*******************************************************************************
 *                               Static Members
 *******************************************************************************/
// States
Root            AppVehicleOperation::root;
Sleeping        AppVehicleOperation::sleeping;
Operating       AppVehicleOperation::operating;
ManualDriving   AppVehicleOperation::manualDriving;
AutoDriving     AppVehicleOperation::autoDriving;
AutoParking     AppVehicleOperation::autoParking;
Cruising        AppVehicleOperation::cruising;
Overtaking      AppVehicleOperation::overtaking;
EmergHandling   AppVehicleOperation::emergHandling;
SpotSearching   AppVehicleOperation::spotSearching;
Maneuvering     AppVehicleOperation::maneuvering;

// Nodes Table of the StateChart (Order Really Matters!)
std::array<state_chart::Node, state_chart::SC_NUM_OF_STATES> AppVehicleOperation::mStateNodes =
{
//  state_chart::Node{state, state's parent index in this array}
    state_chart::Node{AppVehicleOperation::root,          state_chart::SC_INVALID_NODE_IDX},  // root is always parentless
    state_chart::Node{AppVehicleOperation::sleeping,      AppVehicleOperation::eRootIdx},
    state_chart::Node{AppVehicleOperation::operating,     AppVehicleOperation::eRootIdx},
    state_chart::Node{AppVehicleOperation::manualDriving, AppVehicleOperation::eOperatingIdx},
    state_chart::Node{AppVehicleOperation::autoDriving,   AppVehicleOperation::eOperatingIdx},
    state_chart::Node{AppVehicleOperation::autoParking,   AppVehicleOperation::eOperatingIdx},
    state_chart::Node{AppVehicleOperation::cruising,      AppVehicleOperation::eAutoDrivingIdx},
    state_chart::Node{AppVehicleOperation::overtaking,    AppVehicleOperation::eAutoDrivingIdx},
    state_chart::Node{AppVehicleOperation::emergHandling, AppVehicleOperation::eAutoDrivingIdx},
    state_chart::Node{AppVehicleOperation::spotSearching, AppVehicleOperation::eAutoParkingIdx},
    state_chart::Node{AppVehicleOperation::maneuvering,   AppVehicleOperation::eAutoParkingIdx}
};
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <memory>

#include "vehicle_operation.hpp"


using namespace std;
using namespace state_chart;


constexpr const char esc_key = '\33'; // <Esc> key
constexpr const char eventsMenu[] = R"(
Vehicle Operation: press the following to simulate events:
'i' for Ignition On            event
'j' for Ignition Off           event
'a' for Autonomous Driving On  event
'b' for Autonomous Driving Off event
'p' for Automatic Parking On   event
'q' for Automatic Parking Off  event
'd' for Obstacle Detection     event
'c' for Obstacle Cleared       event
'l' for Busy Lane              event
'k' for Clear Lane             event
's' for Parking Spot Found     event
'u' for Parking Successful     event
't' for Parking Action Timeout event
'x' to display events' menu
Press <Esc> to quit.
)";


void displayEventsMenu()
{
    cout << eventsMenu << endl;
}


static AppVehicleOperation appVehicleOperation;

int main()
{
    displayEventsMenu();
    appVehicleOperation.Initialize();       // take the initial transition
    for (;;) {
        // 250 ms delay
        Sleep(250);
        if (_kbhit())
        {
            static Event const ignOn          = {AppVehicleOperation::eIgnitionOnEvent };
            static Event const ignOff         = {AppVehicleOperation::eIgnitionOffEvent };
            static Event const autoCmdOn      = {AppVehicleOperation::eAutonomousDrivingOnEvent };
            static Event const autoCmdOff     = {AppVehicleOperation::eAutonomousDrivingOffEvent };
            static Event const parkCmdOn      = {AppVehicleOperation::eAutomaticParkingOnEvent };
            static Event const parkCmdOff     = {AppVehicleOperation::eAutomaticParkingOffEvent };
            static Event const obsDetected    = {AppVehicleOperation::eObstacleDetectionEvent };
            static Event const obsCleared     = {AppVehicleOperation::eObstacleClearedEvent };
            static Event const busyLane       = {AppVehicleOperation::eBusyLaneEvent };
            static Event const clearLane      = {AppVehicleOperation::eClearLaneEvent };
            static Event const ParkingSpotFd  = {AppVehicleOperation::eParkingSpotFoundEvent };
            static Event const ParkingSuccess = {AppVehicleOperation::eParkingSuccessfulEvent };
            static Event const ParkingTimeout = {AppVehicleOperation::eParkingActionTimeoutEvent };

            Event const *e = nullptr;
            switch (_getch()) 
            {
                case 'i':
                    std::cout << "Ignition On Event : 'i'" << std::endl;
                    e = &ignOn;
                    break;
                case 'j':
                    std::cout << "Ignition Off Event : 'j'" << std::endl;
                    e = &ignOff;
                    break;
                case 'a':
                    std::cout << "Autonomous Driving On Event : 'a'" << std::endl;
                    e = &autoCmdOn;
                    break;
                case 'b':
                    std::cout << "Autonomous Driving Off Event : 'b'" << std::endl;
                    e = &autoCmdOff;
                    break;
                case 'p':
                    std::cout << "Automatic Parking On Event : 'p'" << std::endl;
                    e = &parkCmdOn;
                    break;
                case 'q':
                    std::cout << "Automatic Parking Off Event : 'q'" << std::endl;
                    e = &parkCmdOff;
                    break;
                case 'd':
                    std::cout << "Obstacle Detection Event : 'd'" << std::endl;
                    e = &obsDetected;
                    break;
                case 'c':
                    std::cout << "Obstacle Cleared Event : 'c'" << std::endl;
                    e = &obsCleared;
                    break;
                case 'l':
                    std::cout << "Busy Lane Event : 'l'" << std::endl;
                    e = &busyLane;
                    break;
                case 'k':
                    std::cout << "Clear Lane Event : 'k'" << std::endl;
                    e = &clearLane;
                    break;
                case 's':
                    std::cout << "Parking Spot Found Event : 's'" << std::endl;
                    e = &ParkingSpotFd;
                    break;
                case 'u':
                    std::cout << "Parking Successful Event : 'u'" << std::endl;
                    e = &ParkingSuccess;
                    break;
                case 't':
                    std::cout << "Parking Action Timeout Event : 't'" << std::endl;
                    e = &ParkingTimeout;
                    break;
                case 'x':
                    std::cout << "Display Events Menu : 'x'" << std::endl;
                    displayEventsMenu();
                    break;
                case esc_key:
                    std::cout << "ESC : Bye! Bye!" << std::endl;
                    std::exit(0);
                    break;
                default:
                    std::cout << "Invalid option." << std::endl;
            }
            if (e != nullptr)  // valid keyboard event available?
            {
                appVehicleOperation.SetEvent(*e);  // record and dispatch the event
            }
        }
    }

    return 0;
}
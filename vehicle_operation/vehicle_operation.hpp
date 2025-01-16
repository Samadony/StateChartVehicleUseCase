#ifndef TPMS_OEM_HPP
#define TPMS_OEM_HPP

#include <state_chart.hpp>


class Root;                    // forward declaration
class Sleeping;                // forward declaration
class Operating;               // forward declaration
class ManualDriving;           // forward declaration
class AutoDriving;             // forward declaration
class AutoParking;             // forward declaration
class Cruising;                // forward declaration
class Overtaking;              // forward declaration
class EmergHandling;           // forward declaration
class SpotSearching;           // forward declaration
class Maneuvering;             // forward declaration


class AppVehicleOperation : public state_chart::StateChart
{
public:
    // Types
    enum
    {
        eIgnitionOnEvent = static_cast<state_chart::Signal>(state_chart::eUserSignalsOffset),
        eIgnitionOffEvent,
        eAutonomousDrivingOnEvent,
        eAutonomousDrivingOffEvent,
        eAutomaticParkingOnEvent,
        eAutomaticParkingOffEvent,
        eObstacleDetectionEvent,
        eObstacleClearedEvent,
        eBusyLaneEvent,
        eClearLaneEvent,
        eParkingSpotFoundEvent,
        eParkingSuccessfulEvent,
        eParkingActionTimeoutEvent
    };

    enum
    {
        eRootIdx = 0,
        eSleepingIdx,
        eOperatingIdx,
        eManualDrivingIdx,
        eAutoDrivingIdx,
        eAutoParkingIdx,
        eCruisingIdx,
        eOvertakingIdx,
        eEmergHandlingIdx,
        eSpotSearchingIdx,
        eManeuveringIdx,
        eStatesCount
    };

    // Members
    AppVehicleOperation();
    void Initialize();    // entry point
    void PrintAppVehicleOperation();
    ~AppVehicleOperation();

private:
    void EntryPoint();

    // befriending the states (needs to access members holder shallow and/or deep history)
    friend class Root;
    friend class Sleeping;
    friend class Operating;
    friend class ManualDriving;
    friend class AutoDriving;
    friend class AutoParking;
    friend class Cruising;
    friend class Overtaking;
    friend class EmergHandling;
    friend class SpotSearching;
    friend class Maneuvering;

    // states sole instances shall be part of the class context
    static Root root;
    static Sleeping sleeping;
    static Operating operating;
    static ManualDriving manualDriving;
    static AutoDriving autoDriving;
    static AutoParking autoParking;
    static Cruising cruising;
    static Overtaking overtaking;
    static EmergHandling emergHandling;
    static SpotSearching spotSearching;
    static Maneuvering maneuvering;
    static std::array<state_chart::Node, state_chart::SC_NUM_OF_STATES> mStateNodes;
    
    static_assert(mStateNodes.size() == eStatesCount, "States count mismatch");
    // members
    uint8_t mAutoDrvShallowHistory;      ///< history of state "RelayingData", this is instance specific
    std::array<state_chart::Event, state_chart::SC_CONTEXT_EVENT_QUEUE_CAPACITY> mEventBuffer; ///< context's/application's event's buffer
    
};

#endif  // TPMS_OEM_HPP
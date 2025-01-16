#ifndef TPMS_OEM_STATES_HPP
#define TPMS_OEM_STATES_HPP

#include <state_chart.hpp>


class AppVehicleOperation;               // forward declaration

/*******************************************************************************
 *                               Declarations
 *******************************************************************************/
/*******************************************************************************
 *  Root: Top State 
 *  Direct Children: Sleeping, Operating
 *******************************************************************************/
class Root : public state_chart::State
{
protected:
    virtual void Enter(void *const) override;
    virtual void Initial(void *const) override;
    virtual void Exit(void *const) override;

    virtual void PreHook(void *const) override;
    
    virtual void HandleEvent(void *const, state_chart::Event const *const event) override final; // Must be final, only one demux handler for all events
    virtual void HandleDefault(void *const, state_chart::Event const *const event) override; // default action in case of unidentified event
    virtual void HandleIgnitionOn(void *const, state_chart::Event const *const event);
    virtual void HandleIgnitionOff(void *const, state_chart::Event const *const event);
    virtual void HandleAutoCmdOn(void *const, state_chart::Event const *const event);
    virtual void HandleAutoCmdOff(void *const, state_chart::Event const *const event);
    virtual void HandleParkingCmdOn(void *const, state_chart::Event const *const event);
    virtual void HandleParkingCmdOff(void *const, state_chart::Event const *const event);
    virtual void HandleObstacleDetected(void *const, state_chart::Event const *const event);
    virtual void HandleObstacleCleared(void *const, state_chart::Event const *const event);
    virtual void HandleClearLane(void *const, state_chart::Event const *const event);
    virtual void HandleBusyLane(void *const, state_chart::Event const *const event);
    virtual void HandleSpotFound(void *const, state_chart::Event const *const event);
    virtual void HandleManeuverSuccessful(void *const, state_chart::Event const *const event);
    virtual void HandleParkingActionTimeout(void *const, state_chart::Event const *const event);

    virtual void PostHook(void *const) override;
};

/*******************************************************************************
 * Sleeping (Leaf State/Node)
 * Parent: Root
 *******************************************************************************/
class Sleeping final : public Root
{
protected:
    virtual void Enter(void *const) override;
    virtual void Initial(void *const) override;
    virtual void Exit(void *const) override;

    virtual void PreHook(void *const) override;
    virtual void HandleIgnitionOn(void *const, state_chart::Event const *const event);
    virtual void PostHook(void *const) override;
};

/*******************************************************************************
 * Operating (Composite State/Node)
 * Parent: Root
 * Direct Children: ManualDriving, AutoDriving, AutoParking 
 *******************************************************************************/
class Operating : public Root
{
protected:
    virtual void Enter(void *const) override;
    virtual void Initial(void *const) override;
    virtual void Exit(void *const) override;

    virtual void PreHook(void *const) override;
    virtual void HandleObstacleDetected(void *const, state_chart::Event const *const event);
    virtual void HandleObstacleCleared(void *const, state_chart::Event const *const event);
    virtual void HandleClearLane(void *const, state_chart::Event const *const event);
    virtual void HandleBusyLane(void *const, state_chart::Event const *const event);
    virtual void PostHook(void *const) override;
};

/*******************************************************************************
 * ManualDriving (Leaf State/Node)
 * Parent: Operating
 *******************************************************************************/
class ManualDriving final : public Operating
{
protected:
    virtual void Enter(void *const) override;
    virtual void Initial(void *const) override;
    virtual void Exit(void *const) override;

    virtual void PreHook(void *const) override;
    virtual void HandleIgnitionOff(void *const, state_chart::Event const *const event);
    virtual void HandleAutoCmdOn(void *const, state_chart::Event const *const event);
    virtual void HandleParkingCmdOn(void *const, state_chart::Event const *const event);
    virtual void PostHook(void *const) override;
};

/*******************************************************************************
 * AutoDriving (Composite State)
 * Parent: Operating
 * Direct Children: Cruising, Overtaking, EmergHandling
 *******************************************************************************/
class AutoDriving : public Operating
{
protected:
    virtual void Enter(void *const) override;
    virtual void Initial(void *const) override;
    virtual void Exit(void *const) override;

    virtual void PreHook(void *const) override;
    virtual void HandleAutoCmdOff(void *const, state_chart::Event const *const event);
    virtual void PostHook(void *const) override;
};

/*******************************************************************************
 * Cruising (Leaf State)
 * Parent: AutoDriving
 *******************************************************************************/
class Cruising final : public AutoDriving
{
protected:
    virtual void Enter(void *const) override;
    virtual void Initial(void *const) override;
    virtual void Exit(void *const) override;

    virtual void PreHook(void *const) override;
    virtual void HandleBusyLane(void *const, state_chart::Event const *const event);
    virtual void HandleObstacleDetected(void *const, state_chart::Event const *const event);
    virtual void PostHook(void *const) override;
};

/*******************************************************************************
 * Overtaking (Leaf State)
 * Parent: AutoDriving
 *******************************************************************************/
class Overtaking final : public AutoDriving
{
protected:
    virtual void Enter(void *const) override;
    virtual void Initial(void *const) override;
    virtual void Exit(void *const) override;

    virtual void PreHook(void *const) override;
    virtual void HandleClearLane(void *const, state_chart::Event const *const event);
    virtual void HandleObstacleDetected(void *const, state_chart::Event const *const event);
    virtual void PostHook(void *const) override;
};

/*******************************************************************************
 * EmergHandling (Leaf State)
 * Parent: AutoDriving
 *******************************************************************************/
class EmergHandling final : public AutoDriving
{
protected:
    virtual void Enter(void *const) override;
    virtual void Initial(void *const) override;
    virtual void Exit(void *const) override;

    virtual void PreHook(void *const) override;
    virtual void HandleObstacleCleared(void *const, state_chart::Event const *const event);
    virtual void PostHook(void *const) override;
};

/*******************************************************************************
 * AutoParking (Composite State)
 * Parent: Operating
 * Direct Children: SpotSearching, Maneuvering
 *******************************************************************************/
class AutoParking : public Operating
{
protected:
    virtual void Enter(void *const) override;
    virtual void Initial(void *const) override;
    virtual void Exit(void *const) override;

    virtual void PreHook(void *const) override;
    virtual void HandleParkingCmdOn(void *const, state_chart::Event const *const event); // restart current state
    virtual void HandleParkingCmdOff(void *const, state_chart::Event const *const event); // goto Manual
    virtual void HandleParkingActionTimeout(void *const, state_chart::Event const *const event); // goto Manual
    virtual void HandleObstacleDetected(void *const, state_chart::Event const *const event); // goto SpotSearching or restart it
    virtual void PostHook(void *const) override;
};

/*******************************************************************************
 * SpotSearching (Leaf State)
 * Parent: AutoParking
 *******************************************************************************/
class SpotSearching final : public AutoParking
{
protected:
    virtual void Enter(void *const) override;
    virtual void Initial(void *const) override;
    virtual void Exit(void *const) override;

    virtual void PreHook(void *const) override;
    virtual void HandleSpotFound(void *const, state_chart::Event const *const event);
    virtual void PostHook(void *const) override;
};

/*******************************************************************************
 * Maneuvering (Leaf State)
 * Parent: AutoParking
 *******************************************************************************/
class Maneuvering final : public AutoParking
{
protected:
    virtual void Enter(void *const) override;
    virtual void Initial(void *const) override;
    virtual void Exit(void *const) override;

    virtual void PreHook(void *const) override;
    virtual void HandleManeuverSuccessful(void *const, state_chart::Event const *const event);
    virtual void PostHook(void *const) override;
};

#endif // TPMS_OEM_STATES_HPP
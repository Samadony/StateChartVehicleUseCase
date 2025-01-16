#ifndef STATE_CHART_HPP
#define STATE_CHART_HPP

#include <cstdint>
#include <array>

#include <defines.hpp>
#include <queue.hpp>

//TODO separate the event processor types to files and sub-namespaces according to its use by the application
namespace state_chart
{

/**
 * User shall derive/inherit from this structure to add event specific data
 */
typedef int Signal;
struct Event
{
	Signal signal;
};

// StateChart setup and configurations
// TODO: remove to a config file
/**
 * @brief Maximum depth of the tree/hsm including 
 * @note this number shall be equal to the max number of nested states in the statechart
 */
constexpr uint8_t SC_MAX_HEIRARCHICAL_DEPTH 	   = 4;
constexpr uint8_t SC_NUM_OF_STATES 				   = 11;
constexpr uint8_t SC_INTERNAL_EVENT_QUEUE_CAPACITY = 2;
constexpr uint8_t SC_CONTEXT_EVENT_QUEUE_CAPACITY  = 4;

/**
 * @brief since the RTC nature of the statechart, the user shall provide
 * the means of synchronization here.
 *
 * This definition is used in the statechart implementation, leave it empty
 * ONLY when you are sure that the statechart will run in a non-preemptive context
 *
 * @note this definition SHALL be followed by CRITICAL_SECTION_END
 */
#define SC_CRITICAL_SECTION_START

/**
 * @brief since the RTC nature of the statechart, the user shall provide
 * the means of synchronization here.
 *
 * This definition is used in the statechart implementation, leave it empty
 * ONLY when you are sure that the statechart will run in a non-preemptive context
 *
 * @note this definition SHALL be lead by CRITICAL_SECTION_START
 */
#define SC_CRITICAL_SECTION_END

// Types
enum ReservedStateChartSignals
{
	eTransitionSignal = 0,					///< signal transitioning to or restart of state
	eUserSignalsOffset		    	    	///< signal start index for the user's application
};

/**
 * @brief Abstract class defining state's internal actions
 * @note user shall inherit and implement all internal events in root node
 * @note user shall add event specific actions in root class
 */
class State
{
public:
	// Executed one time only (Enter = State Constructor, Exit = State Destructor, initial is entry point in case of composite state)    
	virtual void Enter(void *const context) = 0;
	virtual void Initial(void *const context) = 0; /* if not leaf state you have to transition */ 
    virtual void Exit(void *const context) = 0;
    // Event Action Hooks, you can add here any repeated sub-actions shared between events of this state
	// emphasizing programming by difference
	// Both hooks get executed at every event reception (prehook eventHandler posthook)
    virtual void PreHook(void *const context) = 0;
    virtual void PostHook(void *const context) = 0;
	// Events De-multiplexer (Only root shall override it)
	virtual void HandleEvent(void *const context, Event const *const event) = 0;
	// default action for other events, you can chose to leave it empty which is synonym to ignoring the event (Only root shall override it)
	virtual void HandleDefault(void *const context, Event const *const event) = 0;
};


constexpr uint8_t SC_INVALID_NODE_IDX = UINT8_MAX;
/** A node of a tree */
struct Node
{
	State& state;
	uint8_t parentStateIdx;
};

 /**
  * @brief A Hierarchical State Machine "HSM" event processor base class
  *
  *	 @note StateChart is not intended to be instantiated directly, but rather serves
  *	 	   as the base class for derivation of state machines in the application
  *	 	   code.
  *  @note Derivatives can be one level of heirarchy .i.e. Finit State Machine "FSM"
  */
class StateChart
{
public:
	/**
	 * @brief Protected constructor of an StateChart.
	 *
	 * Performs the first step of StateChart initialization by assigning the
	 * initial pseudo-state to the currently active state of the state
	 * machine.
	 * @param [in] constant stateTree address
	 * @note The constructor is protected to prevent direct instantiation
	 * 		 of StateChart objects. This class is intended for sub-classing only.
	 */
	StateChart(std::array<Node, SC_NUM_OF_STATES>& Nodes, std::array<Event, SC_CONTEXT_EVENT_QUEUE_CAPACITY>& contextEventsQueue);

	/**
	 * @brief Performs the second step of Hsm initialization, after constructor,
	 *  by,
	 *		- starts from root
	 *		- triggers the top-most initial transition drilling into the leaf state through consecutive
	 *         1) Entry
	 * 	       2) Initial
	 * 		OR
	 * 		- if entryPoint is defined, executes it and its transition
	 *
	 * @param [in] event is a constant pointer to ::Event or a class derived from ::Event.
	 * @param [in] pseudo-state to give control to the user to chose the initial transition
	 *             default value will cause default transitions to occur, same scenario if no
	 *             transition occurs inside entryPoint.
	 * @note Must be called only ONCE before calling Hsm::SetEvent()
	 * @note in case of a derived class from the ::Event, the user shall be careful
	 * 		 since down casting is not type safe
	 */
	virtual void Initialize();

	/**
	 * @brief post an event and start dispatching
     * @param [in] event is a constant pointer the ::Event class or a
     *        class derived from ::Event.
     * @note Must be called after Hsm::Initialize().
	 * @note in case of a derived class from the ::Event, the user shall be careful
	 * 		 since down casting is not type safe
	 */
	void SetEvent(Event const& event);

	/**
	 * @brief post internally to the dispatcher a state transition event.
	 * @param [in] targetStateIdx is the index of the target state not setting
	 * 			   The value will restart current state (leaf)
	 * @note You shall not transition from entry or exit actions!
	 */
	void Transition(uint8_t const targetStateIdx = SC_INVALID_NODE_IDX);

	/**
	 * Virtual destructor
	 */
	virtual ~StateChart() = 0;

PRIVATE:
	// types
	enum TransitionType
	{
		eLeafRestart = 0,
		eAncestorRestart,
		eInitialTransition,
		eTargettedTransition,  // handles transitions to leaf states/nodes and internal/composite ones
		eInvalidTransition
	};

	// helpers
	/**
	 * @brief Dispatch posted events and any subsequent events
     * @param [in] event is a constant pointer the ::Event class or a
     *        class derived from ::Event.
	 * @note in case of a derived class from the ::Event, the user shall be careful
	 * 		 since down casting is not type safe
	 * @note the dispatcher prioritizes the dispatching of internal events over context's events
	 */
	void Dispatch();

	/**
	 * @brief Dispatches a context event
     * @param [in] event is a constant pointer the ::Event class or a
     *        class derived from ::Event.
	 * @note in case of a derived class from the ::Event, the user shall be careful
	 * 		 since down casting is not type safe
	 */
	void DispatchContextEvent();

	/**
	 * @brief Dispatches an internal event
     * @param [in] event is a constant pointer the ::Event class or a
     *        class derived from ::Event.
	 * @note in case of a derived class from the ::Event, the user shall be careful
	 * 		 since down casting is not type safe
	 */
	void DispatchInternalEvent();

	/**
	 * @brief Handle transition request internally
	 */
	void HandleTransition();

	/**
	 * @brief helper to extract list of ancestors upto root
	 * @param [out] ancestorsList, list with length
	 */
	void ExtractNodeAncestorsList(uint8_t nodeAncestorsIdxList[], uint8_t &nodeDepth, uint8_t stateIdx);

	/**
	 * @brief helper used to determine the transition type
	 * @param [in] ancestorsList, list with length
	 */
	TransitionType IdentifyTransitionType(uint8_t nodeAncestorsIdxList[], uint8_t nodeDepth);

	/**
	 * @brief Extracts list of ancestors upto current's and target's Lowest Common Ancestor (LCA)
	 * @param [in] targetAncestorsIdxList first list of ancestors
	 * @param [in] targetAncestorsDepth depth of target ancestors list
	 * @param [in] currentAncestorsIdxList second list of ancestors
	 * @param [in] currentAncestorsDepth depth of current ancestors list
	 * @param [out] targetLcaIdx LCA index
	 * @param [out] currentLcaIdx LCA index
	 * @note LCA is the Lowest Common Ancestor which is the closest ancestor to current and target states
	 * 	     where both share and still the furthest from the root state.
	 */
	void ExtractLca(uint8_t const targetAncestorsList[],
					uint8_t const targetAncestorsDepth,
					uint8_t const currentAncestorsList[],
					uint8_t const currentAncestorsDepth,
					uint8_t &targetLcaIdx,
					uint8_t &currentLcaIdx);

	/**
	 * @brief helper to handle exiting upto a designated stateIdx
	 * @param [in] currentExitIdxList current state exit sequence indices
	 * @param [in] state count to exit
	 * @note execution sequence is FIFO
	 */
	void ExitUpTo(uint8_t const currentExitIdxList[], uint8_t const statesCount);

	/**
	 * @brief helper to handle entering down to a designated stateIdx without
	 * 		  initial transitioning handling
	 * @param [in] targetEntryIdxList target node entry sequence indices
	 * @param [in] state count to enter
	 * @note execution sequence is LIFO
	 */
	void EnterDownTo(uint8_t const targetEntryIdxList[], uint8_t const statesCount);

	/**
	 * @brief check whether transitioning meant to restart current leaf state
	 */
	bool IsLeafRestart();

	/**
	 * @brief check whether transitioning meant to restart root
	 * @note its up to the user to reset state histories in root or not, by doing so
	 *       the statechart is getting fully reset
	 */
	bool IsRootRestart();

	/**
	 * @brief check whether transitioning meant to restart any ancestor of the current leaf state
	 *        subsequently this will restart all states down to leaf
	 */
	bool IsAncestorRestart(uint8_t nodeAncestorsIdxList[], uint8_t nodesCount, uint8_t &ancestorNodeIdx);

	/**
	 * @brief helper checks whether a transition is initial or not
	 */
	bool IsInitialTransition(uint8_t targetStateAncestorsIdxList[], uint8_t nodesCount, uint8_t &ancestorNodeIdx);

	std::array<Node, SC_NUM_OF_STATES>& mNodes; ///< reference to state nodes
	uint8_t mTargetStateIdx;					///< target requested state idx in mNodes
	uint8_t mCurrentStateIdx;		    		///< current active state idx in mNodes
	utils::Queue<Event, SC_CONTEXT_EVENT_QUEUE_CAPACITY> mContextEventsQueue;   ///< context, external, event queue
	utils::Queue<Event, SC_INTERNAL_EVENT_QUEUE_CAPACITY> mInternalEventsQueue;	///< dispatcher's, internal, event queue
};	// class StateChart
}	// namespace state_chart
#endif	// STATE_CHART_HPP
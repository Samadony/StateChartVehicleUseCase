## StateChart Processing Approach

In this StateChart implementation, we adopt a TREE like data structure except instead of data each tree node represents a behaviour or an extension to the ancestors' behviour.

*Terminologies*
Node: used interchangeably with the term "State"
Root: Is the Top State containing ALL other sub states
Leaf Node/State: An atomic state, that contains no other states 


### Processing Flow

- **Top-Down Initialization:**
  - The system initializes from the root state, traversing down to the leaf nodes.

- **Bottom-Up Event Handling:**
  - Leaf nodes primarily handle events, determining whether to process them directly or delegate them up into the hierarchy(ancestors).

### Event Handling Strategy

- **Pre-Hooks Execution:**
  - Executed BEFORE event handling, every time the event is received
  - you put here code, that needs to be executed EVERY time ANY event is received
  - This is different than Enter and Exit actions where they get executed only ONCE
  - PreHook enforces granularity and re-use in your Node/State

- **Leaf State Action:**
  - Decides on event handling, through polymorphic calls 
    - **Immediate Handling:** Processes the event at the leaf node.
    - **Delegation:** Passes the event up with the following options:
      - An ancestor handles the event
      - Leaf itself handles the event
      - A mix where the leaf call an ancestor's implementation

- **Post-Hooks Execution:**
  - Executed AFTER event handling, every time the event is received
  - You put here code, that needs to be executed EVERY time ANY event is received
  - This is different than Enter and Exit actions where they get executed only ONCE
  - PostHook enforces granularity and re-use in your Node/State

## StateChart Rules

- **Internal Events:**
  - The following are treated as internal events:
    - Entry
    - Initial
    - Exit
    - Action Pre-Hook
    - Action Post-Hook

- **Transitions:**
  - Transitions between any states in the Hierarchical State Machine (HSM) are permitted.

- **Hook Invocation:**
  - Only the leaf node's hook executes by default. Users can invoke ancestor hooks as needed.

## Usage
 - Create you ContextClass inheriting state_chart::StateChart
 - Create Root/Top State inheriting from state_chart::State
 - Root State shall implement all event handlers
 - Root shall implement HandleDefault for unnamed events and shall be "final".
 - Root shall implement HandleEvent to De-Multiplex the event and shall be "final"
 - Root shall implement a default event handler per each event concerned by the Context
 - All other states shall inherint from Root, Leaf States shall be "final"


## Future Enhancements

- **Optimized Transitions:**
  - Define specific transition scenarios to improve CPU efficiency.

- **Initialization Adjustments:**
  - Implement targeted and default transitions during initialization to enhance flexibility.

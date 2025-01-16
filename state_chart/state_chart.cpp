#include "state_chart.hpp"
#include <stdio.h>
#include <iostream>

namespace state_chart
{

static std::array<Event, SC_INTERNAL_EVENT_QUEUE_CAPACITY> internalEventsBuffer;

StateChart::StateChart(
	std::array<Node, SC_NUM_OF_STATES>& stateNodes,
	std::array<Event, SC_CONTEXT_EVENT_QUEUE_CAPACITY>& contextEventsBuffer)
	: mNodes(stateNodes),
	mTargetStateIdx(SC_INVALID_NODE_IDX),
	mCurrentStateIdx(SC_INVALID_NODE_IDX),
	mContextEventsQueue(contextEventsBuffer),
	mInternalEventsQueue(internalEventsBuffer)
{
	std::cout << "*** Hsm Constructed ***" << std::endl;
}

// Refine this
void StateChart::Initialize()
{
	SC_CRITICAL_SECTION_START
	std::cout << "*** Hsm Initialize ***" << std::endl;
	Event event;
	// Handle custome entry points by the user
	if(utils::Result::eEmpty != mInternalEventsQueue.Peek(event) && event.signal == eTransitionSignal)
	{
		mInternalEventsQueue.Dequeue();

		uint8_t targetNodeListLength;
		uint8_t targetAncestorsList[SC_MAX_HEIRARCHICAL_DEPTH];
		ExtractNodeAncestorsList(targetAncestorsList, targetNodeListLength, mTargetStateIdx);
		EnterDownTo(targetAncestorsList, targetNodeListLength);
		mNodes[mCurrentStateIdx].state.Initial(this);
	}
	else // default entry point
	{
		mCurrentStateIdx = 0;	// start from root
		mNodes[mCurrentStateIdx].state.Enter(this);
		mNodes[mCurrentStateIdx].state.Initial(this);
	}
	SC_CRITICAL_SECTION_END
	Dispatch();
	
}

void StateChart::Transition(uint8_t const targetStateIdx)
{
	// std::cout <<"*** Transition ***" << std::endl;
	mTargetStateIdx = targetStateIdx;
	if(mInternalEventsQueue.IsFull())
	{
		std::cout << "Internal event queue is full" << std::endl;
		return;
	}
	Event event = {eTransitionSignal};
	mInternalEventsQueue.Enqueue(event);
}

void StateChart::SetEvent(Event const& event)
{
	// std::cout << "*** Set Event ***" << std::endl;
	if(mContextEventsQueue.IsFull())
	{
		// depending on the application you can: 
		// 1- use a ring buffer here
		// 2- ignore
		// 3- raise a fatal error
		return;
	}
	mContextEventsQueue.Enqueue(event);
	Dispatch();
}

void StateChart::Dispatch()
{
	// std::cout << "*** Dispatch ***" << std::endl;
	SC_CRITICAL_SECTION_START
	do
	{
		if(!mContextEventsQueue.IsEmpty())
		{
			// std::cout << "mContextEventsQueue event" << std::endl;
			DispatchContextEvent();
		}

		while(!mInternalEventsQueue.IsEmpty())
		{
			DispatchInternalEvent();
		}
	} while (!mContextEventsQueue.IsEmpty());  // for each one context event handle ALL subsequent internal event(s) (cause and effect(s))
	SC_CRITICAL_SECTION_END
}

void StateChart::DispatchContextEvent()
{
	// std::cout << "*** Dispatch Context Event ***" << std::endl;
	Event event;
	mContextEventsQueue.Peek(event);
	mContextEventsQueue.Dequeue();

	mNodes[mCurrentStateIdx].state.PreHook(this);
	mNodes[mCurrentStateIdx].state.HandleEvent(this, &event);
	mNodes[mCurrentStateIdx].state.PostHook(this);
}

void StateChart::DispatchInternalEvent()
{
	// std::cout << "*** Dispatch Internal Event ***" << std::endl;

	Event event;
	mInternalEventsQueue.Peek(event);
	mInternalEventsQueue.Dequeue();

	switch (event.signal)
	{
		case eTransitionSignal:
			HandleTransition();
			break;
		default:
			break;
	}
}

void StateChart::ExtractNodeAncestorsList(uint8_t nodeAncestorsIdxList[], uint8_t &nodeDepth, uint8_t const stateIdx)
{
	// std::cout << "*** Extract Node Ancestors List ***" << std::endl;
	uint8_t tempIdx = stateIdx;
	for (unsigned i = 0; i < SC_MAX_HEIRARCHICAL_DEPTH; i++)
	{
		nodeAncestorsIdxList[i] = tempIdx;
		if(mNodes[nodeAncestorsIdxList[i]].parentStateIdx == SC_INVALID_NODE_IDX)  // Root reached
		{
			nodeDepth = i + 1;
			break;
		}
		tempIdx = mNodes[tempIdx].parentStateIdx;
	}
}

void StateChart::ExtractLca(uint8_t const targetAncestorsList[],
								uint8_t const targetNodeListLength,
								uint8_t const currentAncestorsList[],
								uint8_t const currentNodeListLength,
								uint8_t &targetLcaIdx,
								uint8_t &currentLcaIdx)
{
	// std::cout << "*** Extract Lca ***" << std::endl;
	for (unsigned targetIdx = 1; targetIdx < targetNodeListLength; targetIdx++)
	{
		for (unsigned currentIdx = 1; currentIdx < currentNodeListLength; currentIdx++)
		{
			if(targetAncestorsList[targetIdx] == currentAncestorsList[currentIdx])
			{
				targetLcaIdx = targetIdx;
				currentLcaIdx = currentIdx;
				return;
			}
		}
	}
}

bool StateChart::IsLeafRestart()
{
	// std::cout << "*** Is Leaf Restart? ***" << std::endl;
	return mTargetStateIdx == mCurrentStateIdx;
}

bool StateChart::IsRootRestart()
{
	// std::cout << "*** Is Root Restart? ***" << std::endl;
	return mTargetStateIdx == 0;  // RootIdx is always = 0
}

bool StateChart::IsAncestorRestart(uint8_t nodeAncestorsIdxList[], uint8_t nodesCount, uint8_t &targetAncestorRestartNodeIdx)
{
	// std::cout << "*** Is Ancestor Restart? ***" << std::endl;
	// it is an ancestor state restart when the target state is an ancestor of current state
	for (unsigned i = 1; i < nodesCount; i++)
	{
		if(mTargetStateIdx == nodeAncestorsIdxList[i])
		{
			targetAncestorRestartNodeIdx = i;
			return true;
		}
	}
	return false;
}

bool StateChart::IsInitialTransition(uint8_t targetStateAncestorsIdxList[], uint8_t nodesCount, uint8_t &currentIdx)
{
	// std::cout << "*** Is Initial Transition? ***" << std::endl;
	// it is initial transition when the current state is an ancestor of the target state
	for (unsigned i = 1; i < nodesCount; i++)
	{
		if (mCurrentStateIdx == targetStateAncestorsIdxList[i])
		{
			currentIdx = i;
			return true;
		}
	}
	return false;
}

void StateChart::EnterDownTo(uint8_t const targetEntryIdxList[], uint8_t const nodesCount)
{
	// std::cout << "*** Enter Down To ***" << std::endl;
	for (signed i = (nodesCount - 1); i >= 0; i--)
	{
		mNodes[targetEntryIdxList[i]].state.Enter(this);
	}
	mCurrentStateIdx = mTargetStateIdx;
}

void StateChart::ExitUpTo(uint8_t const currentExitIdxList[], uint8_t const nodesCount)
{
	// std::cout << "*** Exit Up To ***" << std::endl;
	for (uint8_t i = 0; i < nodesCount; i++)
	{
		// printf("nodeIdx = %d", i);
		mNodes[currentExitIdxList[i]].state.Exit(this);
	}
}

void StateChart::HandleTransition()
{
	// std::cout << "*** Handle Transition ***" << std::endl;
	if(IsLeafRestart())
	{
		mNodes[mCurrentStateIdx].state.Exit(this);
		mNodes[mCurrentStateIdx].state.Enter(this);
		return;
	}

	uint8_t currentNodeListLength;
	uint8_t currentAncestorsList[SC_MAX_HEIRARCHICAL_DEPTH];  // root is the furthest possible ancestor
	ExtractNodeAncestorsList(currentAncestorsList, currentNodeListLength, mCurrentStateIdx);
	
	if(IsRootRestart())
	{
		for (unsigned i = 0; i < currentNodeListLength; i++)
		{
			mNodes[currentAncestorsList[i]].state.Exit(this);
		}
		mNodes[mTargetStateIdx].state.Enter(this);
		mCurrentStateIdx = mTargetStateIdx;
		mNodes[mCurrentStateIdx].state.Initial(this);
		return;
	}

	uint8_t targetAncestorRestartNodeIdx;
	if(IsAncestorRestart(currentAncestorsList, currentNodeListLength, targetAncestorRestartNodeIdx))
	{
		// Exit upto target ancestor
		for (unsigned i = 0; i <= targetAncestorRestartNodeIdx; i++)
		{
			mNodes[currentAncestorsList[i]].state.Exit(this);
		}
		mNodes[mTargetStateIdx].state.Enter(this);
		mCurrentStateIdx = mTargetStateIdx;
		mNodes[mCurrentStateIdx].state.Initial(this);
		return;
	}

	uint8_t targetNodeListLength;
	uint8_t targetAncestorsList[SC_MAX_HEIRARCHICAL_DEPTH];
	// std::cout << "target node Ancestors list" << std::endl;
	// printf("mTargetStateIdx = %d\n", mTargetStateIdx);
	ExtractNodeAncestorsList(targetAncestorsList, targetNodeListLength, mTargetStateIdx);

	uint8_t currentIdx;
	if(IsInitialTransition(targetAncestorsList, targetNodeListLength, currentIdx))
	{
		// Enter down to the target state (excluding current composite state) by passing initial transitions 
		for (signed i = currentIdx - 1; i >= 0; i--)
		{
			mNodes[targetAncestorsList[i]].state.Enter(this);
		}
		mCurrentStateIdx = mTargetStateIdx;
		mNodes[mCurrentStateIdx].state.Initial(this);
		return;
	}

	// std::cout << "IsTargettedTransition" << std::endl;
	uint8_t targetNodeLcaIdx;
	uint8_t currentNodeLcaIdx;
	ExtractLca(targetAncestorsList, targetNodeListLength,
			   currentAncestorsList, currentNodeListLength,
			   targetNodeLcaIdx, currentNodeLcaIdx);

	ExitUpTo(currentAncestorsList, currentNodeLcaIdx);
	EnterDownTo(targetAncestorsList, targetNodeLcaIdx);
	mCurrentStateIdx = mTargetStateIdx;
	mNodes[mCurrentStateIdx].state.Initial(this);
}

StateChart::~StateChart()
{
	std::cout << "*** StateChart Destructed ***" << std::endl;
}

} // namespace state_chart
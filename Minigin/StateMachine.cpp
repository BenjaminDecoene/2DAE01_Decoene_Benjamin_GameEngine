#include "pch.h"
#include "StateMachine.h"
#include "State.h"

void StateMachine::AddState(State* state)
{
	m_States.push_back(state);
}

void StateMachine::SetStartState(State* state)
{
	m_pCurrentState = state;
}

void StateMachine::Update()
{
	m_pCurrentState->Update(this);
}

void StateMachine::TransitionTo(State* state)
{
	//	Do exit function old state
	m_pCurrentState->OnExit();
	//	Set new state
	m_pCurrentState = state;
	//	Do entry function of new state
	m_pCurrentState->OnEntry();
}
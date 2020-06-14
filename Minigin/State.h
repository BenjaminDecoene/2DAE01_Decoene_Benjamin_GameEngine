#pragma once
class StateMachine;

class State
{
public:
	State() = default;
	virtual ~State() = default;
	virtual void Update(StateMachine* stateMachine) = 0;
	virtual void OnEntry(){};
	virtual void OnExit(){};
};
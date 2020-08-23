#pragma once
class StateMachine;

class State
{
public:
	State() = default;
	virtual ~State() = default;
	virtual void Update(StateMachine*){};
	virtual void OnEntry(){};
	virtual void OnExit(){};
};
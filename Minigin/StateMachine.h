#pragma once
class State;

class StateMachine
{
public:
	StateMachine() = default;
	void AddState(State* state);
	void SetStartState(State* state);
	
	void Update();
	void TransitionTo(State* state);
	
	template<typename T>
	T* GetState() const
	{
		for(State* i : m_States)
		{
			auto state = dynamic_cast<T*>(i);
			if(state)
				return state;
		}
		return nullptr;
	}
private:
	std::vector<State*> m_States;
	State* m_pCurrentState;
};
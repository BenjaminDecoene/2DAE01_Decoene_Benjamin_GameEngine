#pragma once
#include <Object.h>

enum State
{
	broken,
	dirt,
	emerald
};

class Tile : public Object
{
public:
	Tile(const b2Vec2& pos, State state);

	State Break();
	//	Getters, setters
	State GetState() const { return m_State; }
private:
	State m_State;
};
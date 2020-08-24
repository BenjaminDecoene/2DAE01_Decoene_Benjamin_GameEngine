#pragma once
#include <Object.h>

enum class TileState
{
	broken,
	dirt,
	emerald
};

class Tile : public Object
{
public:
	Tile(const b2Vec2& pos, TileState state);

	TileState Break();
	//	Getters, setters
	TileState GetState() const { return m_State; }
	void SetState(TileState state);
private:
	TileState m_State;
};
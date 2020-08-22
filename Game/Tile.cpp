#include "pch.h"
#include "Tile.h"
#include "TextureComponent2D.h"

Tile::Tile(const b2Vec2& pos, State state)
	:Object()
	,m_State(state)
{
	m_Transform.SetPosition(pos);

	switch(m_State)
	{
	case dirt:
		AddComponent(new TextureComponent2D(this, "Dirt.jpg", {40, 40}));
		break;
	case emerald:
		AddComponent(new TextureComponent2D(this, "Emerald.png", {40, 40}));
		break;
	case broken:
		break;
	}
}

State Tile::Break()
{
	//	returns true if you broke an emerald
	switch(m_State)
	{
	case dirt:
		m_State = broken;
		RemoveComponent(GetComponent<TextureComponent2D>());
		return dirt;
	case emerald:
		m_State = broken;
		RemoveComponent(GetComponent<TextureComponent2D>());
		return emerald;
	case broken:
		return broken;
	}

	return broken;
}

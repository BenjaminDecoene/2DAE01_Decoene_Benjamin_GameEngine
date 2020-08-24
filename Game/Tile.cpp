#include "pch.h"
#include "Tile.h"
#include "TextureComponent2D.h"

Tile::Tile(const b2Vec2& pos, TileState state)
	:Object()
	,m_State(state)
{
	m_Transform.SetPosition(pos);

	switch(m_State)
	{
	case TileState::dirt:
		AddComponent(new TextureComponent2D(this, "Dirt.jpg", {40, 40}));
		break;
	case TileState::emerald:
		AddComponent(new TextureComponent2D(this, "Emerald.png", {40, 40}));
		break;
	case TileState::broken:
		break;
	}
}

TileState Tile::Break()
{
	//	returns true if you broke an emerald
	switch(m_State)
	{
	case TileState::dirt:
		m_State = TileState::broken;
		RemoveComponent(GetComponent<TextureComponent2D>());
		return TileState::dirt;
	case TileState::emerald:
		m_State = TileState::broken;
		RemoveComponent(GetComponent<TextureComponent2D>());
		return TileState::emerald;
	case TileState::broken:
		return TileState::broken;
	}

	return TileState::broken;
}

void Tile::SetState(TileState state)
{
	Break();
	m_State = state;
	switch(m_State)
	{
	case TileState::dirt:
		AddComponent(new TextureComponent2D(this, "Dirt.jpg", {40, 40}));
		break;
	case TileState::emerald:
		AddComponent(new TextureComponent2D(this, "Emerald.png", {40, 40}));
		break;
	case TileState::broken:
		break;
	}
}
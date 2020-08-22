#include "pch.h"
#include "Tile.h"
#include "TextureComponent2D.h"

Tile::Tile(const b2Vec2& pos)
	:Object()
	,m_State(alive)
{
	m_Transform.SetPosition(pos);
	
	AddComponent(new TextureComponent2D(this, "Dirt.jpg", {40, 40}));
}

void Tile::Break()
{
	switch(m_State)
	{
	case alive:
		m_State = broken;
		RemoveComponent(GetComponent<TextureComponent2D>());
		break;
	default:
		break;
	}
}

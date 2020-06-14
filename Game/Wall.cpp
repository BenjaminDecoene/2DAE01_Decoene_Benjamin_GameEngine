#include "pch.h"
#include "Wall.h"
#include "PhysxComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextureComponent2D.h"

Wall::Wall(const b2Vec2& pos)
{
	//	SetPosition
	SetPosition(pos.x, pos.y);
}

void Wall::Init(const std::string& texture, const b2Vec2& dimensions, Scene* scene)
{
	//	make physx component
	const float ppm = GameInfo::GetInstance().GetPPM();
	//	make the body
	auto bodyDef = new b2BodyDef();
	bodyDef->type = b2_staticBody;
	
	auto physx = new PhysxComponent(this, scene->GetWorld(), bodyDef);
	
	b2PolygonShape boxShape;
	boxShape.SetAsBox((dimensions.x / ppm) / 2, (dimensions.y  / ppm) / 2);
	const auto fixtureDef = new b2FixtureDef();
	fixtureDef->shape = &boxShape;
	fixtureDef->density = 1.0f;
	fixtureDef->friction = 0.3f;
	fixtureDef->restitution = 0.3f;

	physx->AddFixture(fixtureDef);

	AddComponent(physx);

	//	make texture component
	const auto textureComponent = new TextureComponent2D(this, texture, dimensions);
	AddComponent(textureComponent);
}
#pragma once
#include <Object.h>

class Scene;
class PhysxComponent;
class TextureComponent2D;

class Wall : public Object
{
public:
	Wall(const b2Vec2& pos);
	void Init(const std::string& texture, const b2Vec2& dimensions, Scene* scene);
private:
	
};
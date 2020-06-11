#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Transform final
	{
	public:
		Transform() = default;
		Transform(float x, float y) :m_Position({x, y}){};
		const b2Vec2& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y);
		void SetPosition(const b2Vec2& pos) { m_Position = pos; }
	private:
		b2Vec2 m_Position;
	};
}

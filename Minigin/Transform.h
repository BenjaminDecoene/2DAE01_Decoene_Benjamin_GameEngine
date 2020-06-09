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
		Transform(float x, float y, float z) :m_Position({x, y, z}){};
		const b2Vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void SetPosition(const b2Vec3& pos) { m_Position = pos; }
	private:
		b2Vec3 m_Position;
	};
}

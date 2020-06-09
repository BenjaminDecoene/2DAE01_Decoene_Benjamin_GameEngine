#pragma once
#include <Box2D.h>

namespace dae
{
	class SceneObject;
	class Scene
	{
	public:
		Scene(const std::string& name);
		void Add(SceneObject* object);

		void Update();
		void Render(float interpolation) const;
		std::string GetName() const { return m_Name; }
		b2World* GetWorld() const { return m_World; }
		
		virtual ~Scene();

	private: 
		std::string m_Name;
		std::vector<SceneObject*> m_Objects{};

		static unsigned int m_IdCounter;

		b2World* m_World;
	};

}

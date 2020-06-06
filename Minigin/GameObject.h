#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"

namespace dae
{
	class GameObject : public SceneObject
	{
	public:
		void Update() override;

		void AddComponent(Component* component);
		template<typename T>
		inline T GetComponent()
		{
			for(Component* i : m_pComponents)
			{
				if(static_cast<T>(i) != nullptr)
				{
					return static_cast<T>(i);
				}
			}
			return nullptr;
		}
		void SetPosition(float x, float y);
		Transform GetTransform() const { return m_Transform; }

		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		std::vector<Component*> m_pComponents;
	};
}

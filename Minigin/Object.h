#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"

namespace dae
{
	class Object : public SceneObject
	{
	public:
		Object() = default;
		//	Base functions
		void Update() override;
		void Render() const override;

		void AddComponent(Component* component);
		
		//	Setters, getters
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

		//	Rule of 5
		virtual ~Object();
		Object(const Object& other) = delete;
		Object(Object&& other) = delete;
		Object& operator=(const Object& other) = delete;
		Object& operator=(Object&& other) = delete;

	protected:
		Transform m_Transform;
		std::vector<Component*> m_pComponents;
	};
}
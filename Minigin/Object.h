#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"
#include "Subject.h"

class Object : public Subject, public SceneObject
{
public:
	Object() = default;
	//	Base functions
	void Update() override;
	void Render(float interpolation) const override;

	void AddComponent(Component* component);
	
	//	Setters, getters
	template<typename T>
	T* GetComponent() const
	{
		for(Component* i : m_pComponents)
		{
			auto component = dynamic_cast<T*>(i);
			if(component)
			{
				return component;
			}
		}
		return nullptr;
	}
	void SetPosition(float x, float y);
	void SetRotation(float angle) { m_Rotation = angle; }
	Transform GetTransform() const { return m_Transform; }
	float GetRotation() const { return m_Rotation; }

	//	Rule of 5
	virtual ~Object();
	Object(const Object& other) = delete;
	Object(Object&& other) = delete;
	Object& operator=(const Object& other) = delete;
	Object& operator=(Object&& other) = delete;

protected:
	Transform m_Transform;
	float m_Rotation = 0.f;
	std::vector<Component*> m_pComponents;
};

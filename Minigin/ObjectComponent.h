#pragma once
#include "Transform.h"

class ObjectComponent
{
public:
	ObjectComponent(const std::string& type);

	void SetParentTransform(dae::Transform& parentTransform) { m_pParentTransform = &parentTransform; }
	virtual void Update() = 0;
	virtual void Render() const {};
protected:
	std::string m_Type;
	dae::Transform* m_pParentTransform;
};

#pragma once
#include "Object.h"
#include <string>

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Notify(const Object& object, const std::string& event) = 0;
};
#pragma once

#include "Utils/StringExt.h"

#include <stdint.h>
#include <string>
#include <vector>

struct ClassTestComponent
{
	int32_t ComponentField1;
	std::string ComponentField2;

	bool operator==(const ClassTestComponent& other) const
	{
		return ComponentField1 == other.ComponentField1 && ComponentField2 == other.ComponentField2;
	}

	std::string ToString() const
	{
		return Reflecto::StringExt::Format<std::string>("{ComponentField1=%u,ComponentField2=%s}", ComponentField1, ComponentField2.c_str());
	}
};

struct ClassTestComposition
{
	std::string Field1;
	std::vector<ClassTestComponent> Components;

	bool operator==(const ClassTestComposition& other) const
	{
		return Field1 == other.Field1 && Components == other.Components;
	}

	std::string ToString() const
	{
		std::string componentsStr = Reflecto::StringExt::Join<std::string>(Components, ",", &ClassTestComponent::ToString);
		return Reflecto::StringExt::Format<std::string>("{Field1=%s, Components=[%s]}", Field1.c_str(), componentsStr.c_str());
	}
};
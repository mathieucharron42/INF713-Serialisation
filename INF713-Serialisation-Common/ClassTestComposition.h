#pragma once

#include "Utils/StringExt.h"

#include <stdint.h>
#include <string>
#include <vector>

using namespace Reflecto::Utils;

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
		return StringExt::Format<std::string>("{ComponentField1=%u,ComponentField2=%s}", ComponentField1, ComponentField2.c_str());
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
		std::string componentsStr = StringExt::Join<std::string>(Components, ",", &ClassTestComponent::ToString);
		return StringExt::Format<std::string>("{Field1=%s, Components=[%s]}", Field1.c_str(), componentsStr.c_str());
	}
};
#pragma once

#include "Utils/StringExt.h"

#include <stdint.h>
#include <string>

struct ClassTest
{
	uint32_t Field1 = 0;
	float Field2 = 0.f;
	std::string Field3;

	bool operator==(const ClassTest& other) const
	{
		return Field1 == other.Field1 && Field2 == other.Field2 && Field3 == other.Field3;
	}

	std::string ToString() const
	{
		return Reflecto::Utils::StringExt::Format<std::string>("{Field1=%u,Field2=%f,Field2=%s}", Field1, Field2, Field3.c_str());
	}
};
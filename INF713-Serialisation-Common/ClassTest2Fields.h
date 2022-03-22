#pragma once

#include "Utils/StringExt.h"

#include <stdint.h>
#include <string>

struct ClassTest2Fields
{
	uint32_t Field1;
	uint64_t Field2;

	bool operator==(const ClassTest2Fields& other) const
	{
		return Field1 == other.Field1 && Field2 == other.Field2;
	}

	std::string ToString() const
	{
		return Reflecto::Utils::StringExt::Format<std::string>("{Field1=%u,Field2=%llu}", Field1, Field2);
	}
};
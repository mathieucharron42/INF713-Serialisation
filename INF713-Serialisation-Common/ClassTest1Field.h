#pragma once

#include "Utils/StringExt.h"

#include <stdint.h>
#include <string>

struct ClassTest1Field
{
	uint32_t Field1;

	bool operator==(const ClassTest1Field& other) const
	{
		return Field1 == other.Field1;
	}

	std::string ToString() const
	{
		return Reflecto::StringExt::Format<std::string>("{Field=%u}", Field1);
	}
};
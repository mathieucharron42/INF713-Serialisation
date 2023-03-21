#pragma once

#include "Utils/StringExt.h"

#include <stdint.h>
#include <string>

#pragma pack(push, 1)
struct ClassTest2FieldsPod
{
	uint32_t Field1;
	uint64_t Field2;

	bool operator==(const ClassTest2FieldsPod& other) const
	{
		return Field1 == other.Field1 && Field2 == other.Field2;
	}

	std::string ToString() const
	{
		return Reflecto::StringExt::Format<std::string>("{Field1=%u,Field2=%llu}", Field1, Field2);
	}
};
static_assert(std::is_pod<ClassTest2FieldsPod>::value, "ClassTest2FieldsPod is not a pod");
#pragma pack(pop)
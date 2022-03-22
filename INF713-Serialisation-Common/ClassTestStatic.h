#pragma once

#include "Utils/StringExt.h"

#include <algorithm>
#include <stdint.h>
#include <string>

struct ClassTestStatic
{
	char FieldArray[30];

	bool operator==(const ClassTestStatic& other) const
	{
		return std::equal(std::begin(FieldArray), std::end(FieldArray), std::begin(other.FieldArray));
	}

	std::string ToString() const
	{
		return Reflecto::Utils::StringExt::Format<std::string>("{Field1=%s}", FieldArray);
	}
};
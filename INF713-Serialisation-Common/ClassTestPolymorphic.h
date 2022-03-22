#pragma once


#include "Utils/StringExt.h"

#include <stdint.h>
#include <string>

struct BaseTestClass
{
	virtual void Method() { }
};

struct ClassTestPolymorphic : public BaseTestClass
{
	uint32_t Field1;
	virtual void Method() override { }

	bool operator==(const ClassTestPolymorphic& other) const
	{
		return Field1 == other.Field1;
	}

	std::string ToString() const
	{
		return Reflecto::Utils::StringExt::Format<std::string>("{Field1=%u}", Field1);
	}
};
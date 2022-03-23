#pragma once


#include "Utils/StringExt.h"

#include <stdint.h>
#include <string>

using namespace Reflecto::Utils;

struct BaseTestClass
{
	uint32_t Field1;

	bool operator==(const BaseTestClass& other) const
	{
		return Field1 == other.Field1;
	}

	virtual std::string ToString() const
	{
		return StringExt::Format<std::string>("{Field1=%u}", Field1);
	}
};

struct ClassTestPolymorphic : public BaseTestClass
{
	uint32_t Field2;

	bool operator==(const ClassTestPolymorphic& other) const
	{
		return BaseTestClass::operator==(other) && Field2 == other.Field2;
	}

	virtual std::string ToString() const override
	{
		return StringExt::Format<std::string>("{Parent=%s,Field1=%u}", BaseTestClass::ToString().c_str(), Field1);
	}
};
#pragma once

#include "ClassTest.h"
#include "ManualSerialisationTechnique.h"

#include "Common/Ensure.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

namespace ManualSerializationTechnique
{
	template<>
	void Serialization(const ClassTest& instance, std::ostream& stream)
	{
		std::stringstream ss;
		{
			ss << "Field1" << kSeparator;
			ss << instance.Field1 << kSeparator;

			ss << "Field2" << kSeparator;
			ss << instance.Field2 << kSeparator;

			ss << "Field3" << kSeparator;
			ss << Escape(instance.Field3) << kSeparator;

			ss << std::endl;
		}
		stream << ss.str();
	}

	template<>
	void Deserialization(ClassTest& instance, std::istream& stream)
	{
		std::string fieldName;

		std::stringstream ss(std::string{ std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>{} });

		ss >> fieldName;
		ensure(fieldName == "Field1");
		ss >> instance.Field1;

		ss >> fieldName;
		ensure(fieldName == "Field2");
		ss >> instance.Field2;

		ss >> fieldName;
		ensure(fieldName == "Field3");
		ss >> instance.Field3;
		instance.Field3 = Unescape(instance.Field3);
	}
}
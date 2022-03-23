#pragma once

#include "ClassTest.h"
#include "ManualMaisonSerialisationTechnique.h"

#include "Common/Ensure.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

namespace ManualMaisonSerializationTechnique
{
	template<>
	void Serialization(const ClassTest& instance, std::ostream& stream)
	{
		std::stringstream ss;
		{
			Write("Field1", instance.Field1, ss);
			Write("Field2", instance.Field2, ss);
			Write("Field3", instance.Field3, ss);
		}
		stream << ss.str();
	}

	template<>
	void Deserialization(ClassTest& instance, std::istream& stream)
	{
		std::string fieldName;

		std::stringstream ss(std::string{ std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>{} });
		{
			Read("Field1", instance.Field1, ss);
			Read("Field2", instance.Field2, ss);
			Read("Field3", instance.Field3, ss);
		}
	}
}
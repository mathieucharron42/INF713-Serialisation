#pragma once

#include "ClassTest.h"

#include "Common/Ensure.h"
#include "Utils/StringExt.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

namespace ManualMaisonSerializationTechnique
{
	const std::string kSeparator = " ";
	const std::string kEscapeSeparator = "\\";

	template<typename type>
	void Write(const std::string& field, const type& value, std::stringstream& stream)
	{
		stream << field << kSeparator;
		stream << value << kSeparator;
	}

	template<>
	void Write(const std::string& field, const std::string& value, std::stringstream& stream)
	{
		stream << field << kSeparator;
		std::string escapedValue = Reflecto::StringExt::ReplaceAll(value, kSeparator, kEscapeSeparator);
		stream << escapedValue << kSeparator;
	}

	template<typename type>
	void Read(const std::string& field, type& value, std::stringstream& stream)
	{
		std::string readField;
		stream >> readField;
		ensure(readField == field);
		stream >> value;
	}

	template<>
	void Read(const std::string& field, std::string& value, std::stringstream& stream)
	{
		std::string readField;
		stream >> readField;
		ensure(readField == field);
		std::string escapedValue;
		stream >> escapedValue;
		value = Reflecto::StringExt::ReplaceAll(escapedValue, kEscapeSeparator, kSeparator);
	}

	template<typename type>
	void Serialization(const type& instance, std::ostream& stream) { }

	template<typename type>
	void Deserialization(type& instance, std::istream& stream) { }

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
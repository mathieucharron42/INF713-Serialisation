#pragma once

#include "Common/Ensure.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

namespace ManualMaisonSerializationTechnique
{
	const std::string kSeparator = " ";
	const std::string kEscapeSeparator = "\\";

	template<typename type>
	void Serialization(const type& instance, std::ostream& stream) { }

	template<typename type>
	void Deserialization(type& instance, std::istream& stream) { }

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
		std::string escapedValue = Reflecto::Utils::StringExt::ReplaceAll(value, kSeparator, kEscapeSeparator);
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
		value = Reflecto::Utils::StringExt::ReplaceAll(escapedValue, kEscapeSeparator, kSeparator);
	}
}
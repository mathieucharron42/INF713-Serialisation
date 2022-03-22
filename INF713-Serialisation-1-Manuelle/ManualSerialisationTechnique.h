#pragma once

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

namespace ManualSerializationTechnique
{
	const std::string kSeparator = " ";
	const std::string kEscapeSeparator = "\\";

	template<typename type>
	void Serialization(const type& instance, std::ostream& stream) { }

	template<typename type>
	void Deserialization(type& instance, std::istream& stream) { }


	std::string Escape(std::string source)
	{
		return Reflecto::Utils::StringExt::ReplaceAll(source, kSeparator, kEscapeSeparator);
	}

	std::string Unescape(std::string source)
	{
		return Reflecto::Utils::StringExt::ReplaceAll(source, kEscapeSeparator, kSeparator);
	}
}
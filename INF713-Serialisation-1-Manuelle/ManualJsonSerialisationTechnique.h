#pragma once

#include "Serialization/Writer/JsonSerializationWriter.h"
#include "Serialization/Reader/JsonSerializationReader.h"

#include <iostream>

namespace ManualJsonSerializationTechnique
{
	template<typename type>
	void Serialization(const type& instance, std::ostream& stream) { }

	template<typename type>
	void Deserialization(type& instance, std::istream& stream) { }
}
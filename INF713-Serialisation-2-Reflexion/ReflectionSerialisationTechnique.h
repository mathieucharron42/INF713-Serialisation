#pragma once

#include "Serialization/Serializer.h"
#include "Serialization/Reader/JsonSerializationReader.h"
#include "Serialization/Writer/JsonSerializationWriter.h"

namespace ReflectionSerializationTechnique
{
	template<class type>
	void Serialization(const Reflecto::Serialization::Serializer& serializer, const type& instance, std::ostream& stream)
	{
		Reflecto::Serialization::JsonSerializationWriter writer;
		serializer.Serialize(instance, writer);
		writer.Export(stream);
	}

	template<class type>
	void Deserialization(const Reflecto::Serialization::Serializer& serializer, type& instance, std::istream& stream)
	{
		Reflecto::Serialization::JsonSerializationReader reader;
		reader.Import(stream);
		serializer.Deserialize(instance, reader);
	}
}

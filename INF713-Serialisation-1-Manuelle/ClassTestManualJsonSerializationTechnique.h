#pragma once

#pragma once

#pragma once

#include "ClassTest.h"
#include "ManualJsonSerialisationTechnique.h"

#include "Serialization/Writer/JsonSerializationWriter.h"
#include "Serialization/Reader/JsonSerializationReader.h"
#include "Common/Ensure.h"

#include <iostream>

namespace ManualJsonSerializationTechnique
{
	template<>
	void Serialization(const ClassTest& instance, std::ostream& stream)
	{
		Reflecto::Serialization::JsonSerializationWriter writer;
		ensure(writer.WriteBeginObject());
		{
			ensure(writer.WriteBeginObjectProperty("Field1"));
			{
				ensure(writer.WriteUnsignedInteger32(instance.Field1));
			}
			ensure(writer.WriteEndObjectProperty());

			ensure(writer.WriteBeginObjectProperty("Field2"));
			{
				ensure(writer.WriteFloat(instance.Field2));
			}
			ensure(writer.WriteEndObjectProperty());

			ensure(writer.WriteBeginObjectProperty("Field3"));
			{
				ensure(writer.WriteString(instance.Field3));
			}
			ensure(writer.WriteEndObjectProperty());
		}
		ensure(writer.WriteEndObject());
		ensure(writer.Export(stream));
	}

	template<>
	void Deserialization(ClassTest& instance, std::istream& stream)
	{
		Reflecto::Serialization::JsonSerializationReader reader;

		reader.Import(stream);

		reader.ReadBeginObject();
		{
			std::string fieldName;
			ensure(reader.ReadBeginObjectProperty(fieldName));
			{
				ensure(fieldName == "Field1");
				ensure(reader.ReadUnsignedInteger32(instance.Field1));
			}
			ensure(reader.ReadEndObjectProperty());

			ensure(reader.ReadBeginObjectProperty(fieldName));
			{
				ensure(fieldName == "Field2");
				ensure(reader.ReadFloat(instance.Field2));
			}
			ensure(reader.ReadEndObjectProperty());

			ensure(reader.ReadBeginObjectProperty(fieldName));
			{
				ensure(fieldName == "Field3");
				ensure(reader.ReadString(instance.Field3));
			}
			ensure(reader.ReadEndObjectProperty());
		}
		ensure(reader.ReadEndObject());
	};
}
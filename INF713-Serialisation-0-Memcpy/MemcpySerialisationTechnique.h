#pragma once

#include <ostream>

#include "Utils/IOExt.h"

namespace MemcpySerializationTechnique
{
	template<class type>
	void Serialization(const type& instance, std::ostream& stream)
	{
		Reflecto::IOExt::WriteBytes(instance, stream);
	}

	template<class type>
	void Deserialization(type& instance, std::istream& stream)
	{
		Reflecto::IOExt::ReadBytes(instance, stream);
	}
}
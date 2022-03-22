#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

namespace SerializationWorkbench
{
	template<typename serialization_func_t, typename deserialization_func_t, typename object_t>
	void Test(const std::string& type, const std::string& technique, const std::string& format, serialization_func_t serializationFunc, deserialization_func_t deserializationFunc, const std::string& fileName, const object_t& original)
	{
		std::cout << "Sérialisation / Déserialisation Test" << std::endl;
		std::cout << "Technique=" << technique << " " << "Format=" << format << std::endl;
		std::cout << "Instance=" << type << original.ToString() << std::endl;

		std::fstream stream{ fileName, std::ios::in | std::ios::out | std::ios::trunc };
		assert(stream.is_open());

		bool success = false;
		try
		{
			// serialize
			{
				object_t originalCopy = original;
				serializationFunc(originalCopy, stream);
				stream.flush();
			}

			object_t deserialized;

			// deserialize
			{
				stream.seekg(0, std::ios::beg);
				deserializationFunc(deserialized, stream);
			}

			success = original == deserialized;
		}
		catch (...)
		{
			success = false;
		}

		auto writeColoredFunc = [](const std::string& message, WORD color)
		{
			const static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			CONSOLE_SCREEN_BUFFER_INFO console_info;
			GetConsoleScreenBufferInfo(hConsole, &console_info);

			SetConsoleTextAttribute(hConsole, color);
			std::cout << message;
			SetConsoleTextAttribute(hConsole, console_info.wAttributes);
		};

		const std::string message = (success ? "Succès" : "Échec");
		const WORD color = (success ? FOREGROUND_GREEN | FOREGROUND_INTENSITY : FOREGROUND_RED | FOREGROUND_INTENSITY);

		std::cout << "Résultat: ";
		writeColoredFunc(message, color);
		std::cout << std::endl;

		std::cout << "Voir '" << fileName << "' pour les données sérialisées" << std::endl;
		std::cout << std::endl;
	}
}
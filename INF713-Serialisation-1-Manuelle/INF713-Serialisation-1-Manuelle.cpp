// INF713-Serialisation-1-Manuelle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ClassTestManualSerialisationTechnique.h"
#include "ClassTestManualJsonSerializationTechnique.h"

#include "ClassTest.h"
#include "SerializationWorkbench.h"

int main()
{
	std::locale::global(std::locale{ "" }); // Correction des accents

	ClassTest instance = { 42, 3.14159f, "Bonjour! Ceci est un test avec une longue string!" };

	SerializationWorkbench::Test(
		"ClassTest", "Manuelle", "Texte maison",
		ManualSerializationTechnique::Serialization<ClassTest>,
		ManualSerializationTechnique::Deserialization<ClassTest>,
		"manuelle_ClassTest.txt",
		instance
	);

	SerializationWorkbench::Test(
		"ClassTest", "Manuelle", "Texte maison",
		ManualJsonSerializationTechnique::Serialization<ClassTest>,
		ManualJsonSerializationTechnique::Deserialization<ClassTest>,
		"manuelle_ClassTest.json",
		instance
	);
}
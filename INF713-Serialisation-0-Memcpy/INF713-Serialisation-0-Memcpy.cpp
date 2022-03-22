// INF713-Serialisation-0-Memcpy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MemcpySerialisationTechnique.h"

#include "ClassTest.h"
#include "ClassTest1Field.h"
#include "ClassTest2Fields.h"
#include "ClassTest2FieldsPod.h"
#include "ClassTestPolymorphic.h"
#include "ClassTestStatic.h"
#include "SerializationWorkbench.h"

int main()
{
	std::locale::global(std::locale{ "" }); // Correction des accents

	ClassTest1Field test1Field = { std::numeric_limits<uint32_t>::max() };
	SerializationWorkbench::Test(
		"ClassTest1Field", "Memcpy", "Binaire brute",
		MemcpySerializationTechnique::Serialization<ClassTest1Field>,
		MemcpySerializationTechnique::Deserialization<ClassTest1Field>,
		"memcpy_ClassTest1Field.bin",
		test1Field
	);

	// Notez le l'endianess....!
	ClassTest1Field test1FieldIndianess = { 1 };
	SerializationWorkbench::Test(
		"ClassTest1Field", "Memcpy", "Binaire brute",
		MemcpySerializationTechnique::Serialization<ClassTest1Field>,
		MemcpySerializationTechnique::Deserialization<ClassTest1Field>,
		"memcpy_ClassTest1FieldIndianess.bin",
		test1FieldIndianess
	);

	// Notez le padding....!
	ClassTest2Fields test2Field = { std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint64_t>::max() };
	SerializationWorkbench::Test(
		"ClassTest2Fields", "Memcpy", "Binaire brute",
		MemcpySerializationTechnique::Serialization<ClassTest2Fields>,
		MemcpySerializationTechnique::Deserialization<ClassTest2Fields>,
		"memcpy_ClassTest2Fields.bin",
		test2Field
	);

	// POD pour enlever le padding.... Ouf :)
	ClassTest2FieldsPod test2FieldPod = { std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint64_t>::max() };
	SerializationWorkbench::Test(
		"ClassTest2FieldsPod", "Memcpy", "Binaire brute",
		MemcpySerializationTechnique::Serialization<ClassTest2FieldsPod>,
		MemcpySerializationTechnique::Deserialization<ClassTest2FieldsPod>,
		"memcpy_ClassTest2FieldsPod.bin",
		test2FieldPod
	);


	// Notez qu'un tableau statique peut être sérialisé
	ClassTestStatic testStatic = { "Bonjour! Ceci est un test!" };
	SerializationWorkbench::Test(
		"testStatic", "Memcpy", "Binaire brute",
		MemcpySerializationTechnique::Serialization<ClassTestStatic>,
		MemcpySerializationTechnique::Deserialization<ClassTestStatic>,
		"memcpy_ClassTestStatic.bin",
		testStatic
	);

	// Notez la vtable sérialisé ! Très problématique !!
	ClassTestPolymorphic testPolymorphicClass;
	testPolymorphicClass.Field1 = std::numeric_limits<uint32_t>::max();
	SerializationWorkbench::Test(
		"ClassTestPolymorphic", "Memcpy", "Binaire brute",
		MemcpySerializationTechnique::Serialization<ClassTestPolymorphic>,
		MemcpySerializationTechnique::Deserialization<ClassTestPolymorphic>,
		"memcpy_ClassTestPolymorphic.bin",
		testPolymorphicClass
	);

	// Boom !
	// Notez qu'une classe avec référence externe, pointeur ou allocation dynamique ne peut pas
	// sérialiser correctement ! Pire, la désérialisation va échouer à et entraîner un comportement non déterministe.
	//ClassTest testLongStringField = { std::numeric_limits<uint32_t>::max(), 3.14159f, "Bonjour! Ceci est un test avec une longue string!" };
	//SerializationWorkbench::Test(
	//	"TestClass", "Memcpy", "Binaire brute",
	//	MemcpySerializationTechnique::Serialization<ClassTest>,
	//	MemcpySerializationTechnique::Deserialization<ClassTest>,
	//	"memcpy_TestLongStringField.bin",
	//	testLongStringField
	//);
}
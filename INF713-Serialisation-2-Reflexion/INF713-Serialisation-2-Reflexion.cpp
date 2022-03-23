// INF713-Serialisation-2-Reflexion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Type/Type.h"
#include "Type/TypeFactory.h"
#include "Type/TypeDescriptor.h"
#include "Type/TypeDescriptorFactory.h"
#include "Type/TypeLibrary.h"
#include "Type/TypeLibraryFactory.h"
#include "Serialization/Serializer.h"
#include "Serialization/SerializerFactory.h"
#include "Serialization/Strategy/SerializationStrategy.h"

#include "ClassTest.h"
#include "ClassTestComposition.h"
#include "SerializationWorkbench.h"
#include "ReflectionSerialisationTechnique.h"

#include <iostream>

int main()
{
	std::locale::global(std::locale{ "" }); // Correction des accents

	// Définir la réflexion

	Reflecto::Reflection::TypeLibrary typeLibrary = Reflecto::Reflection::TypeLibraryFactory{}
		.Add<int32_t>("int32")
		.Add<uint32_t>("uint32")
		.Add<float>("float")
		.Add<bool>("bool")
		.Add<std::string>("string")
		.Add<ClassTest>("TestClass")
		.Add<ClassTestComponent>("ClassTestComponent")
		.Add<ClassTestComposition>("ClassTestComposition")
		.Add<std::vector<ClassTestComponent>>("std::vector<ClassTestComponent>")
	.Build();

	Reflecto::Reflection::TypeDescriptor classTestDescriptor = Reflecto::Reflection::TypeDescriptorFactory<ClassTest>{ typeLibrary }
		.RegisterMember(&ClassTest::Field1, "Field1")
		.RegisterMember(&ClassTest::Field2, "Field2")
		.RegisterMember(&ClassTest::Field3, "Field3")
	.Build();

	Reflecto::Reflection::TypeDescriptor classTestComponentDescriptor = Reflecto::Reflection::TypeDescriptorFactory<ClassTestComponent>{ typeLibrary }
		.RegisterMember(&ClassTestComponent::ComponentField1, "ComponentField1")
		.RegisterMember(&ClassTestComponent::ComponentField2, "ComponentField2")
	.Build();

	Reflecto::Reflection::TypeDescriptor classTestCompositionDescriptor = Reflecto::Reflection::TypeDescriptorFactory<ClassTestComposition>{ typeLibrary }
		.RegisterMember(&ClassTestComposition::Components, "Components")
		.RegisterMember(&ClassTestComposition::Field1, "Field1")
	.Build();


	// Définir la sérialisation

	Reflecto::Serialization::Serializer serializer = Reflecto::Serialization::SerializerFactory{ typeLibrary }
		.LearnType<int32_t, Reflecto::Serialization::Int32SerializationStrategy>()
		.LearnType<uint32_t, Reflecto::Serialization::UInt32SerializationStrategy>()
		.LearnType<float, Reflecto::Serialization::FloatSerializationStrategy>()
		.LearnType<bool, Reflecto::Serialization::BooleanSerializationStrategy>()
		.LearnType<std::string, Reflecto::Serialization::StringSerializationStrategy>()
		.LearnType<ClassTest, Reflecto::Serialization::ObjectSerializationStrategy<ClassTest>>(classTestDescriptor)
		.LearnType<ClassTestComponent, Reflecto::Serialization::ObjectSerializationStrategy<ClassTestComponent>>(classTestComponentDescriptor)
		.LearnType<ClassTestComposition, Reflecto::Serialization::ObjectSerializationStrategy<ClassTestComposition>>(classTestCompositionDescriptor)
		.LearnType<std::vector<ClassTestComponent>, Reflecto::Serialization::VectorSerializationStrategy<std::vector<ClassTestComponent>>>()
	.Build();
	serializer.SetSerializationFormat(Reflecto::Serialization::SerializationFormat::Short);
	

	ClassTest instance = { 42, 3.14159f, "Bonjour! Ceci est un test avec une longue string!" };

	SerializationWorkbench::Test(
		"ClassTest", "Réflexion", "json",
		std::bind(ReflectionSerializationTechnique::Serialization<ClassTest>, serializer, _1, _2),
		std::bind(ReflectionSerializationTechnique::Deserialization<ClassTest>, serializer, _1, _2),
		"reflexion_ClassTest.json",
		instance
	);

	ClassTestComposition instanceComposition;
	instanceComposition.Field1 = "Test!!";
	instanceComposition.Components = { { 1, "Premier component"}, {2, "Deuxieme component avec une plus longue string"}, {3, "Troisieme et dernier component"} };
	
	SerializationWorkbench::Test(
		"ClassComposition", "Réflexion", "json",
		std::bind(ReflectionSerializationTechnique::Serialization<ClassTestComposition>, serializer, _1, _2),
		std::bind(ReflectionSerializationTechnique::Deserialization<ClassTestComposition>, serializer, _1, _2),
		"reflexion_ClassTestComposition.json",
		instanceComposition
	);
}
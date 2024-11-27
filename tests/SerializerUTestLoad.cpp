#include "pch.h"

#include "..\..\Serializer\Serializer.h"
#include "..\..\Serializer\XMLProcessor.h"
#include "CppUnitTest.h"

#include <sstream>
#include <codecvt>
#include <locale>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SerializerUTest
{
	TEST_CLASS(SerializerUTestLoad)
	{
	public:
		TEST_METHOD(TestLoad_Object1WithPath_Success)
		{
			// Arrange
			std::string file_name{"test_file_class_1_load.xml"};

			//Act
			std::stringstream objectSerialized = serializer.LoadFromFile(basePath + file_name, FileType::XML);
			std::string resultStream{ objectSerialized.str() }, expectedStream{ "{ { 1 } { hello } { 3.16 } } " };

			//Assert
			Assert::AreEqual(expectedStream, resultStream);
			Assert::IsTrue(objectSerialized.good());
		
		}			
		TEST_METHOD(TestLoad_Object2WithPath_Success)
		{
			std::string file_name{"test_file_class_2_load.xml"};

			std::stringstream objectSerialized = serializer.LoadFromFile(basePath + file_name, FileType::XML);
			std::string resultStream{ objectSerialized.str() }, expectedStream{ "{ { 1 } { { first } { second } { third } } { { { { 1 } { hello } { 3.16 } } { { 2 } { string2 } { 5.0 } } } { { { 34 } { goof } { 8.0 } } { { 2 } { string2 } { 5.0 } } } } { 2 } { 1 } } " };
			
			Assert::AreEqual(expectedStream, resultStream);
			Assert::IsTrue(objectSerialized.good());
		}	
		TEST_METHOD(TestLoad_VectorIntWithPath_Success)
		{
			std::string file_name{"test_file_vector_int_load.xml"};

			std::stringstream objectSerialized = serializer.LoadFromFile(basePath + file_name, FileType::XML);
			std::string resultStream{ objectSerialized.str() }, expectedStream{ "{ { 1 } { 2 } { 3 } } " };

			Assert::AreEqual(expectedStream, resultStream);
			Assert::IsTrue(objectSerialized.good());
		}		
		TEST_METHOD(TestLoad_VectorClass1WithPath_Success)
		{
			std::string file_name{ "test_file_vector_class_load.xml" };

			std::stringstream objectSerialized = serializer.LoadFromFile(basePath + file_name, FileType::XML);
			std::string resultStream{ objectSerialized.str() }, expectedStream{ "{ { { 1 } { this } { 1.0 } } { { 2 } { that } { 2.0 } } { { 3 } { thus } { 3.0 } } } " };

			Assert::AreEqual(expectedStream, resultStream);
			Assert::IsTrue(objectSerialized.good());
		}
		TEST_METHOD(TestLoad_VectorVectorIntWithPath_Success)
		{
			std::string file_name{"test_file_vector_vector_int_load.xml"};

			std::stringstream objectSerialized = serializer.LoadFromFile(basePath + file_name, FileType::XML);
			std::string resultStream{ objectSerialized.str() }, expectedStream{ "{ { { 1 } { 2 } { 3 } } { { 1 } { 2 } { 3 } } } " };

			Assert::AreEqual(expectedStream, resultStream);
			Assert::IsTrue(objectSerialized.good());
		}			
		TEST_METHOD(TestLoad_VectorVectorStringWithPath_Success)
		{
			std::string file_name{"test_file_vector_vector_string_load.xml"};

			std::stringstream objectSerialized = serializer.LoadFromFile(basePath + file_name, FileType::XML);
			std::string resultStream{ objectSerialized.str() }, expectedStream{ "{ { { hello } { from } { here } } { { goodbye } { from } { here } } } " };

			Assert::AreEqual(expectedStream, resultStream);
			Assert::IsTrue(objectSerialized.good());
		}

	private:
		std::string basePath{ BASE_PATH};
		CSerializer serializer;
	};
}

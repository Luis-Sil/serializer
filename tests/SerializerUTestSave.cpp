#include "pch.h"
#include "..\..\Serializer\Serializer.h"
#include "..\..\Serializer\XMLProcessor.h"
#include "CppUnitTest.h"

#include <sstream>
#include <codecvt>
#include <locale>
#include <fstream>
#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SerializerUTest
{
	TEST_CLASS(SerializerUTestSave)
	{
	public:

		TEST_METHOD(TestSave_EmptyObjectWithPath_Success)
		{
			std::string file_name{ "test_empty_object_save_1.xml" };
			std::stringstream objectSerialized{ "[class]{[field1]{ }[field2]{[field1]{ }}[field3]{[field1]{ }}[field4]{ }}" };

			serializer.SaveToFile(basePath + file_name, objectSerialized);
			std::stringstream objectSerializedP = serializer.LoadFromFile(basePath + file_name, FileType::XML);
			
			std::string resultStream{ objectSerializedP.str() }, expectedStream{ "{ {  } { {  } } { {  } } {  } } " };

			Assert::AreEqual(expectedStream, resultStream);
		}
		
		TEST_METHOD(TestSave_ObjectWithPath_Success)
		{
			std::string file_name{ "test_object_save_1.xml" };
			std::stringstream objectSerialized{ "[class]{[field1]{1}[field2]{string}[field3]{1.511}}" };

			serializer.SaveToFile(basePath + file_name, objectSerialized);
			std::stringstream objectSerializedP = serializer.LoadFromFile(basePath + file_name, FileType::XML);
			
			std::string resultStream{ objectSerializedP.str() }, expectedStream{ "{ { 1 } { string } { 1.511 } } " };

			Assert::AreEqual(expectedStream, resultStream);
		}

		TEST_METHOD(TestSave_ComplexObjectWithPath_Success)
		{
			std::string file_name{ "test_object_save_2.xml" };
			std::stringstream objectSerialized{ "[class]{[class]{[field1]{2}[field2]{[element1]{you}[element2]{do}[element3]{you}}[field3]{[class]{[field1]{1}[field2]{1.0}[field3]{string}}[class]{[field1]{4}[field2]{6.0}[field3]{string}}[class]{[field1]{10}[field2]{1.65}[field3]{hello}}}}[field4]{string}[field5]{1.511}}" };

			serializer.SaveToFile(basePath + file_name, objectSerialized);
			std::stringstream objectSerializedP = serializer.LoadFromFile(basePath + file_name, FileType::XML);
			
			std::string resultStream{ objectSerializedP.str() }, expectedStream{ "{ { { 2 } { { you } { do } { you } } { { { 1 } { 1.0 } { string } } { { 4 } { 6.0 } { string } } { { 10 } { 1.65 } { hello } } } } { string } { 1.511 } } " };

			Assert::AreEqual(expectedStream, resultStream);
		}

		TEST_METHOD(TestSave_VectorIntObjectWithPath_Success)
		{
			std::string file_name{ "test_vector_int_save.xml" };
			std::stringstream objectSerialized{ "[vector]{[element1]{23}[element2]{62}[element3]{193}[element4]{1}}" };

			serializer.SaveToFile(basePath + file_name, objectSerialized);
			std::stringstream objectSerializedP = serializer.LoadFromFile(basePath + file_name, FileType::XML);
			
			std::string resultStream{ objectSerializedP.str() }, expectedStream{ "{ { 23 } { 62 } { 193 } { 1 } } " };

			Assert::AreEqual(expectedStream, resultStream);
		}

		TEST_METHOD(TestSave_VectorClassObjectWithPath_Success)
		{
			std::string file_name{ "test_vector_class_save.xml" };
			std::stringstream objectSerialized{ "[vector]{[class]{[field1]{1.0}[field 2]{string with spaces}[field3]{[field1]{1.0}[field2]{2.0}[field3]{3.0}}}}" };

			serializer.SaveToFile(basePath + file_name, objectSerialized);
			std::stringstream objectSerializedP = serializer.LoadFromFile(basePath + file_name, FileType::XML);
			
			std::string resultStream{ objectSerializedP.str() }, expectedStream{ "{ { { 1.0 } { string with spaces } { { 1.0 } { 2.0 } { 3.0 } } } } " };

			Assert::AreEqual(expectedStream, resultStream);
		}

		TEST_METHOD(TestSave_VectorVectorIntObjectWithPath_Success)
		{
			std::string file_name{ "test_vector_vector_int_save.xml" };
			std::stringstream objectSerialized{ "[vector]{[vector]{[element1]{23}[element2]{62}[element3]{193}[element4]{1}}[vector]{[element1]{43}[element2]{1560}[element3]{25}[element4]{0}}}" };

			serializer.SaveToFile(basePath + file_name, objectSerialized);
			std::stringstream objectSerializedP = serializer.LoadFromFile(basePath + file_name, FileType::XML);

			std::string resultStream{ objectSerializedP.str() }, expectedStream{ "{ { { 23 } { 62 } { 193 } { 1 } } { { 43 } { 1560 } { 25 } { 0 } } } " };
			
			Assert::AreEqual(expectedStream, resultStream);
		}

		TEST_METHOD(TestSave_VectorVectorStringObjectWithPath_Success)
		{
			std::string file_name{ "test_vector_vector_string_save.xml" };
			std::stringstream objectSerialized{ "[vector]{[vector]{[element1]{hello}[element2]{from}[element3]{here}}[vector]{[element1]{goodbye}[element2]{from}[element3]{here}}}" };

			serializer.SaveToFile(basePath + file_name, objectSerialized);
			std::stringstream objectSerializedP = serializer.LoadFromFile(basePath + file_name, FileType::XML);

			std::string resultStream{ objectSerializedP.str() }, expectedStream{ "{ { { hello } { from } { here } } { { goodbye } { from } { here } } } " };

			Assert::AreEqual(expectedStream, resultStream);
		}
	private:
		std::string basePath{ BASE_PATH };
		CSerializer serializer;
	};

}
#include "pch.h"
#include "CppUnitTest.h"
#include "TestTypes.h"

#include "..\..\GeneralTools\StdLibStreamOperators.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GeneralToolsUTest
{
	TEST_CLASS(StdLibOperatorsUTest)
	{
	public:

		TEST_METHOD(VecInputStreamOperator_InputStreamVecInt_Correct)
		{
			std::stringstream vectorStream{ "{ { 1 } { 2 } { 3 } { 4 } }" };

			std::vector<int> vInt, expected{ 1,2,3,4 };
			vectorStream >> vInt;

			Assert::IsTrue(vInt == expected);
			Assert::IsTrue(!vectorStream.fail());
		}
		TEST_METHOD(VecOutputStreamOperator_OutputStreamVecInt_Correct)
		{
			std::stringstream vectorStream;
			std::vector<int> vInt{ 1,2,3,4 };

			vectorStream << vInt;

			std::string expectedStream{ "[int]{1}[int]{2}[int]{3}[int]{4}" }, resultStream{ vectorStream.str() };

			Assert::IsTrue(expectedStream == resultStream);
		}
		TEST_METHOD(VecInputStreamOperator_InputStreamVecVecInt_Correct)
		{
			std::stringstream vectorStream{ "{ { { 1 } { 2 } } { { 3 } { 4 } } }" };

			std::vector<std::vector<int>> vvInt, expected{ {1,2},{3,4} };
			vectorStream >> vvInt;

			Assert::IsTrue(vvInt == expected);
			Assert::IsTrue(!vectorStream.fail());
		}
		TEST_METHOD(VecOutputStreamOperator_OutputStreamVecVecInt_Correct)
		{
			std::stringstream vectorStream;
			std::vector<std::vector<int>> vvInt{ {1,2},{3,4} };

			vectorStream << vvInt;

			std::string expectedStream{ "[vector int]{[int]{1}[int]{2}}[vector int]{[int]{3}[int]{4}}" }, resultStream{ vectorStream.str() };

			Assert::IsTrue(expectedStream == resultStream);
		}
		TEST_METHOD(VecInputStreamOperator_InputStreamVecString_Correct)
		{
			std::stringstream vectorStream{ "{ { hello world } { goodbye cruel world } }" };

			std::vector<std::string> vStr, expected{ "hello world", "goodbye cruel world" };
			vectorStream >> vStr;

			Assert::IsTrue(vStr == expected);
			Assert::IsTrue(!vectorStream.fail());
		}
		TEST_METHOD(VecOutputStreamOperator_OutputStreamVecString_Correct)
		{
			std::stringstream vectorStream{};

			std::vector<std::string> vStr{ "hello world", "goodbye cruel world" };
			vectorStream << vStr;

			std::string expectedStream{ "[string]{hello world}[string]{goodbye cruel world}" }, resultStream{ vectorStream.str() };
			Assert::IsTrue(resultStream == expectedStream);
		}
		TEST_METHOD(VecInputStreamOperator_InputStreamVecClass_Correct)
		{
			std::stringstream vectorStream{ "{ { { 2 } { 1.0 } } { { 1 } { 3.14 } } { { 5 } { 3.67 } } }" };

			std::vector<ClassWithBasicTypes> vObj, expected{ ClassWithBasicTypes{2, 1.0}, ClassWithBasicTypes{1, 3.14}, ClassWithBasicTypes{5, 3.67} };
			vectorStream >> vObj;

			Assert::IsTrue(vObj == expected);
			Assert::IsTrue(!vectorStream.fail());
		}
		TEST_METHOD(VecOutputStreamOperator_OutputStreamVecClassBasicTypes_Correct)
		{
			std::stringstream vectorStream{};

			std::vector<ClassWithBasicTypes> vObj{ ClassWithBasicTypes{2, 1.0}, ClassWithBasicTypes{1, 3.14}, ClassWithBasicTypes{5, 3.67} };
			vectorStream << vObj;

			std::string expectedStream{ "[ClassWithBasicTypes]{[a]{2}[b]{1.000000}}[ClassWithBasicTypes]{[a]{1}[b]{3.140000}}[ClassWithBasicTypes]{[a]{5}[b]{3.670000}}" }, resultStream{ vectorStream.str() };

			Assert::IsTrue(resultStream == expectedStream);
		}
		TEST_METHOD(VecInputStreamOperator_InputStreamVecClassWithContainers_Correct)
		{
			std::stringstream vectorStream{ "{ { { { { { 1 } { 2 } { 3 } } { big string } { { 1 } { 2.560000 } } } } { { { that is } { tuesday } } { { such a sunny day } { BSP } } } } }" };

			std::vector<ClassWithContainersTypes> vObj, expected{ ClassWithContainersTypes{} };
			vectorStream >> vObj;

			Assert::IsTrue(vObj == expected);
			Assert::IsTrue(!vectorStream.fail());
		}
		TEST_METHOD(VecOutputStreamOperator_OutputStreamVecClassWithContainers_Correct)
		{
			std::stringstream vectorStream{};

			std::vector<ClassWithContainersTypes> vObj{ ClassWithContainersTypes{} };
			vectorStream << vObj;

			std::string expectedStream{ "[ClassWithContainersTypes]{[a]{[ClassWithComposedTypes]{[a]{[int]{1}[int]{2}[int]{3}}[b]{big string}[c]{[a]{1}[b]{2.560000}}}}[b]{[vector string]{[string]{that is}[string]{tuesday}}[vector string]{[string]{such a sunny day}[string]{BSP}}}}" }, resultStream{ vectorStream.str() };

			Assert::IsTrue(resultStream == expectedStream);
		}
	};
}

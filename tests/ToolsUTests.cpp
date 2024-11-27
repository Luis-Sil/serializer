#include "pch.h"
#include "CppUnitTest.h"
#include "TestTypes.h"

#include "..\..\GeneralTools\Tools.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GeneralToolsUTest
{

	TEST_CLASS(ToolsUTest)
	{
	public:

		TEST_METHOD(BuildObjectTagBasedOnType)
		{
			std::string tagForBasicType = BuildTypeTagForStreamableObject<int>();
			std::string tagForString = BuildTypeTagForStreamableObject<std::string>();
			std::string tagForVector = BuildTypeTagForStreamableObject<std::vector<std::string>>();
			std::string tagForVectorOfVector = BuildTypeTagForStreamableObject<std::vector<std::vector<ClassWithBasicTypes>>>();
			std::string tagForVectorOfVectorOfVector = BuildTypeTagForStreamableObject<std::vector<std::vector<std::vector<Enum>>>>();
			std::string tagForClass = BuildTypeTagForStreamableObject<ClassWithBasicTypes>();

			Assert::IsTrue(tagForBasicType == "[int]");
			Assert::IsTrue(tagForString == "[string]");
			Assert::IsTrue(tagForVector == "[vector string]");
			Assert::IsTrue(tagForVectorOfVector == "[vector vector ClassWithBasicTypes]");
			Assert::IsTrue(tagForVectorOfVectorOfVector == "[vector vector vector Enum]");
			Assert::IsTrue(tagForClass == "[ClassWithBasicTypes]");
		}

		TEST_METHOD(BuildObjectTagCustom)
		{
			std::string tagForBasicType = BuildCustomTagForStreamableObject("integer field");
			std::string tagForString = BuildCustomTagForStreamableObject("whatever", "args", 2);

			Assert::IsTrue(tagForBasicType == "[integer field]");
			Assert::IsTrue(tagForString == "[whatever args 2]");
		}

		TEST_METHOD(GetStreamableField_CorrectType)
		{
			int i{ 1 };
			double j{ 2.0 };
			std::string str{ "hello" };
			Enum e{ Enum::A };
			ClassWithBasicTypes c{};

			std::string i_stream{ GetStreamableObject(i) },
				j_stream{ GetStreamableObject(j) },
				str_stream{ GetStreamableObject(str) },
			e_stream{ GetStreamableObject(e) },
			c_stream{ GetStreamableObject(c) };

			Assert::IsTrue(i_stream == "{1}");
			Assert::IsTrue(j_stream == "{2.000000}");
			Assert::IsTrue(str_stream == "{hello}");
			Assert::IsTrue(e_stream == "{0}");
			Assert::IsTrue(c_stream == "{[a]{1}[b]{2.560000}}");
		}

		TEST_METHOD(Test_EraseEnclosedString_Func)
		{
			std::string str{ "hello people, here is an {enclosed string} for you" };
			std::string expectedStr{ "hello people, here is an  for you" };

			Assert::IsTrue(EraseNextEnclosedString(str, { '{', '}' }));
			Assert::IsTrue(str == expectedStr);


			str = "here is {another}, but you want to remove the {second one}";
			expectedStr = "here is {another}, but you want to remove the ";
			Assert::IsTrue(EraseNextEnclosedString(str, { '{', '}' }, 20));
			Assert::IsTrue(str == expectedStr);

		}

		TEST_METHOD(Test_ProcessVectorTag)
		{
			std::string resultingTag = Detail::ProcessVectorTypeName<std::vector<int>>();
			Assert::IsTrue(resultingTag == "vector<int>");
			resultingTag = Detail::ProcessVectorTypeName<std::vector<std::vector<double>>>();
			Assert::IsTrue(resultingTag == "vector<vector<double>>");
			resultingTag = Detail::ProcessVectorTypeName<std::vector<std::vector<std::vector<float>>>>();
			Assert::IsTrue(resultingTag == "vector<vector<vector<float>>>");
			resultingTag = Detail::ProcessVectorTypeName<std::vector<ClassWithBasicTypes>>();
			Assert::IsTrue(resultingTag == "vector<ClassWithBasicTypes>");
			resultingTag = Detail::ProcessVectorTypeName<std::vector<std::vector<ClassWithComposedTypes>>>();
			Assert::IsTrue(resultingTag == "vector<vector<ClassWithComposedTypes>>");
			resultingTag = Detail::ProcessVectorTypeName<std::vector<std::vector<std::vector<Enum>>>>();
			Assert::IsTrue(resultingTag == "vector<vector<vector<Enum>>>");
			resultingTag = Detail::ProcessVectorTypeName<std::vector<std::string>>();
			Assert::IsTrue(resultingTag == "vector<string>");
			resultingTag = Detail::ProcessVectorTypeName<std::vector<std::vector<std::string>>>();
			Assert::IsTrue(resultingTag == "vector<vector<string>>");
		}
	};
}
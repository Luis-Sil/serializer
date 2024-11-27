#include "test_types.h"
#include "tools.h"
#include "stream_operators.h"

std::istream& operator>>(std::istream& inputStream, ClassWithBasicTypes& obj)
{
	std::string objectStr;
	if (GetNextEnclosedString(inputStream, objectStr, { FIELD_LEFT_ENCLOSER, FIELD_RIGHT_ENCLOSER }))
	{
		std::stringstream objectStream{ objectStr };
		GetObjectFromStream(obj.a, objectStream);
		GetObjectFromStream(obj.b, objectStream);

		if (objectStream.fail())
			inputStream.setstate(objectStream.rdstate());
	}
	else
		inputStream.setstate(std::ios_base::badbit);

	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const ClassWithBasicTypes& obj)
{
	outputStream << BuildCustomTagForStreamableObject("ClassWithBasicTypes");
	outputStream << FIELD_LEFT_ENCLOSER;
	outputStream << BuildCustomTagForStreamableObject("a") << GetStreamableObject(obj.a);
	outputStream << BuildCustomTagForStreamableObject("b") << GetStreamableObject(obj.b);
	outputStream << FIELD_RIGHT_ENCLOSER;

	return outputStream;
}

bool operator==(const ClassWithBasicTypes& lhs, const ClassWithBasicTypes& rhs)
{
	std::stringstream streamLhs, streamRhs;
	streamLhs << lhs;
	streamRhs << rhs;
	return streamLhs.str() == streamRhs.str();
}

std::istream& operator>>(std::istream& inputStream, ClassWithComposedTypes& obj)
{
	std::string objectStr;
	if (GetNextEnclosedString(inputStream, objectStr, { FIELD_LEFT_ENCLOSER, FIELD_RIGHT_ENCLOSER }))
	{
		std::stringstream objectStream{ objectStr };
		GetObjectFromStream(obj.a, objectStream);
		GetObjectFromStream(obj.b, objectStream);

		if (inputStream.fail())
			inputStream.setstate(inputStream.rdstate());
	}
	else
		inputStream.setstate(std::ios_base::badbit);

	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const ClassWithComposedTypes& obj)
{
	outputStream << BuildCustomTagForStreamableObject("ClassWithComposedTypes");
	outputStream << FIELD_LEFT_ENCLOSER;
	outputStream << BuildCustomTagForStreamableObject("a") << GetStreamableObject(obj.a);
	outputStream << BuildCustomTagForStreamableObject("b") << GetStreamableObject(obj.b);
	outputStream << BuildCustomTagForStreamableObject("c") << GetStreamableObject(obj.c);
	outputStream << FIELD_RIGHT_ENCLOSER;
	return outputStream;
}

bool operator==(const ClassWithComposedTypes& lhs, const ClassWithComposedTypes& rhs)
{
	std::stringstream streamLhs, streamRhs;
	streamLhs << lhs;
	streamRhs << rhs;
	return streamLhs.str() == streamRhs.str();
}

std::istream& operator>>(std::istream& inputStream, ClassWithContainersTypes& obj)
{
	std::string objectStr;
	if (GetNextEnclosedString(inputStream, objectStr, { FIELD_LEFT_ENCLOSER, FIELD_RIGHT_ENCLOSER }))
	{
		std::stringstream objectStream{ objectStr };
		GetObjectFromStream(obj.a, objectStream);
		GetObjectFromStream(obj.b, objectStream);

		if (inputStream.fail())
			inputStream.setstate(inputStream.rdstate());
	}
	else
		inputStream.setstate(std::ios_base::badbit);

	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const ClassWithContainersTypes& obj)
{
	outputStream << BuildCustomTagForStreamableObject("ClassWithContainerTypes");
	outputStream << FIELD_LEFT_ENCLOSER;
	outputStream << BuildCustomTagForStreamableObject("a") << GetStreamableObject(obj.a);
	outputStream << BuildCustomTagForStreamableObject("b") << GetStreamableObject(obj.b);
	outputStream << FIELD_RIGHT_ENCLOSER;
	return outputStream;
}

bool operator==(const ClassWithContainersTypes& lhs, const ClassWithContainersTypes& rhs)
{
	std::stringstream streamLhs, streamRhs;
	streamLhs << lhs;
	streamRhs << rhs;
	return streamLhs.str() == streamRhs.str();
}

#pragma once
#include <vector>
#include <string>
#include <istream>
#include <ostream>

enum class Enum
{
	A = 0,
	B = 1,
	C = 2
};

struct ClassWithBasicTypes
{
	int a = 1;
	double b = 2.56;
};

struct ClassWithComposedTypes
{
	std::vector<int> a = { 1,2,3 };
	std::string b = "big string";
	ClassWithBasicTypes c{};
};

struct ClassWithContainersTypes
{
	std::vector<ClassWithComposedTypes> a = { ClassWithComposedTypes{} };
	std::vector<std::vector<std::string>> b = { {"that is", "tuesday"}, {"such a sunny day", "BSP"} };
};

std::istream& operator>>(std::istream& inputStream, ClassWithBasicTypes& obj);

std::ostream& operator<<(std::ostream& outputStream, const ClassWithBasicTypes& obj);

bool operator==(const ClassWithBasicTypes& lhs, const ClassWithBasicTypes& rhs);

std::istream& operator>>(std::istream& inputStream, ClassWithComposedTypes& obj);

std::ostream& operator<<(std::ostream& outputStream, const ClassWithComposedTypes& obj);

bool operator==(const ClassWithComposedTypes& lhs, const ClassWithComposedTypes& rhs);

std::istream& operator>>(std::istream& inputStream, ClassWithContainersTypes& obj);

std::ostream& operator<<(std::ostream& outputStream, const ClassWithContainersTypes& obj);

bool operator==(const ClassWithContainersTypes& lhs, const ClassWithContainersTypes& rhs);
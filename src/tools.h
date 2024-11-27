#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "reflection_utils.h"

#include <string>
#include <sstream>
#include <istream>
#include <vector>
#include <type_traits>
#include <cstdarg>
#include <algorithm>

#define FIELD_TAG_LEFT_ENCLOSER "["
#define FIELD_TAG_RIGHT_ENCLOSER "]"
#define FIELD_LEFT_ENCLOSER "{"
#define FIELD_RIGHT_ENCLOSER "}"

/// <summary>
/// Finds and erases the next enclosed string surrounded by a pair of enclosers. 
/// The search can start at an arbitrary position in the string, being defaulted to zero.
/// </summary>
/// <param name="str">string to be search</param>
/// <param name="enclosers">chars surrounding the string to be erased</param>
/// <param name="npos">starting position of the search</param>
/// <returns>true if success, false otherwise</returns>
bool EraseNextEnclosedString(std::string& str, const std::pair<char, char>& enclosers, size_t npos = 0);

/// <summary>
/// Extracts the next string in a stream enclosed by a pair of encloser strings.
/// </summary>
/// <param name="stream">stream to extract from</param>
/// <param name="str">extracted string</param>
/// <returns>bool: false if no matching encloser was found </returns>
bool GetNextEnclosedString(std::istream& stream, std::string& str, const std::pair<std::string, std::string>& enclosers);


/// <summary>
/// Processing tools for trimming the type name of a vector or class types.
/// </summary>
namespace Detail
{
	template <typename T>
	std::string ProcessVectorTypeName()
	{
		if constexpr (!is_vector_v<T>)
			static_assert(false, "Can't be used with non-vector type.");
		else
		{
			std::string vectorTag{ type_name<T> };
			size_t pos = vectorTag.find("allocator");

			//remove what is after "allocator" inside "<...>"
			while (pos != vectorTag.npos)
			{
				EraseNextEnclosedString(vectorTag, { '<', '>' }, pos);
				pos = vectorTag.find("allocator", pos + 1, 9);
			}

			//remove what is after "string" inside "<...>"
			pos = vectorTag.find("string");
			while (pos != vectorTag.npos)
			{
				EraseNextEnclosedString(vectorTag, { '<', '>' }, pos);
				pos = vectorTag.find("string", pos + 1, 6);
			}

			//remove all words in next dictionary
			std::array<std::string, 10> dict = { "class", "struct", "allocator", "basic", "enum", "std", "::", "_", " ", "," };
			for (auto& word : dict)
			{
				pos = vectorTag.find(word);
				while (pos != vectorTag.npos)
				{
					vectorTag.erase(std::next(vectorTag.begin(), pos), std::next(vectorTag.begin(), pos + word.size()));
					pos = vectorTag.find(word);
				}
			}

			//finally, process '<' and '>' characters as they will be escaped in an xml file
			std::replace(vectorTag.begin(), vectorTag.end(), '<', ' ');
			while (vectorTag.back() == '>')
				vectorTag.pop_back();

			return vectorTag;
		}
	}

	template<typename T>
	std::string ProcessClassTypeName()
	{
		if constexpr (is_vector_v<T> || std::is_same_v<T, std::string>)
			static_assert(false, "Can't be used with vector and string types.");
		else
		{
			std::string classTag{ type_name<T> };

			//remove all words in next dictionary
			std::array<std::string, 3> dict = { "class", "struct", " " };
			for (auto& word : dict)
			{
				size_t pos = classTag.find(word);
				while (pos != classTag.npos)
				{
					classTag.erase(std::next(classTag.begin(), pos), std::next(classTag.begin(), pos + word.size()));
					pos = classTag.find(word);
				}
			}

			return classTag;
		}
	}

	template<typename T>
	std::string ProcessEnumTypeName()
	{
		if constexpr (std::is_enum_v<T>)
		{
			std::string enumTag{ type_name<T> };

			//remove all words in next dictionary
			std::array<std::string, 2> dict = { "enum", " " };
			for (auto& word : dict)
			{
				size_t pos = enumTag.find(word);
				while (pos != enumTag.npos)
				{
					enumTag.erase(std::next(enumTag.begin(), pos), std::next(enumTag.begin(), pos + word.size()));
					pos = enumTag.find(word);
				}
			}

			return enumTag;
		}
		else
			static_assert(false, "Can't be used with other types than enum.");
	}
}

/// <summary>
/// takes an object value and transforms it to a streamable string.
/// </summary>
/// <typeparam name="T">object type</typeparam>
/// <param name="value">object value</param>
/// <returns>object streamable string</returns>
template <typename T>
std::string GetStreamableObject(const T& value)
{
	std::string toReturn{ FIELD_LEFT_ENCLOSER };

	if constexpr (std::is_same_v<T, std::string>)
		toReturn += value;
	else if constexpr (std::is_enum_v<T>)
		toReturn += std::to_string(static_cast<typename std::underlying_type<T>::type>(value));
	else if constexpr (!std::is_class_v<T>)
		toReturn += std::to_string(value);
	else if constexpr (is_vector_v<T>)
	{
		std::stringstream objStream{};
		objStream << value;
		toReturn += objStream.str();
	}
	else
	{
		std::stringstream objStream{};
		objStream << value;
		toReturn = objStream.str();
		EraseNextEnclosedString(toReturn, { '[', ']' });//erase object tag

		return toReturn;
	}

	toReturn += FIELD_RIGHT_ENCLOSER;
	return toReturn;
}

/// <summary>
/// takes an object and extracts it from a stream. Only works if
/// the object type is streamable. Example: if a class does not
/// overload the stream operators, this tool cannot be used.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="stream"></param>
/// <returns></returns>
template <typename T>
bool GetObjectFromStream(T& object, std::istream& stream)
{
	if constexpr (std::is_same_v<T, std::string>)
		return GetNextEnclosedString(stream, object, { FIELD_LEFT_ENCLOSER, FIELD_RIGHT_ENCLOSER });
	else if constexpr (std::is_enum_v<T> || !std::is_class_v<T>)
	{
		std::string tmp{};
		stream >> tmp;
		stream >> object;
		stream >> tmp;

		if (stream.fail())
			return false;

		return true;
	}
	else
	{
		stream >> object;
		if (stream.fail())
			return false;

		return true;
	}
}

/// <summary>
/// builds a tag for a streamable object based on its type.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template <typename T>
std::string BuildTypeTagForStreamableObject()
{
	std::ostringstream tag;
	tag << FIELD_TAG_LEFT_ENCLOSER;

	if constexpr (std::is_same_v<T, std::string>)
		tag << "string";
	else if constexpr (is_vector_v<T>)
		tag << Detail::ProcessVectorTypeName<T>();
	else if constexpr (std::is_enum_v<T>)
		tag << Detail::ProcessEnumTypeName<T>();
	else
		tag << Detail::ProcessClassTypeName<T>();

	tag << FIELD_TAG_RIGHT_ENCLOSER;
	return tag.str();
}

/// <summary>
/// builds a custom tag for a streamable object. 
/// </summary>
/// <typeparam name="Arg"></typeparam>
/// <typeparam name="...Args"></typeparam>
/// <param name="arg"></param>
/// <param name="...args"></param>
/// <returns></returns>
template <typename Arg, typename... Args>
std::string BuildCustomTagForStreamableObject(Arg&& arg, Args&&... args)
{
	std::ostringstream tag;

	tag << FIELD_TAG_LEFT_ENCLOSER;
	tag << std::forward<Arg>(arg);
	((tag << ' ' << std::forward<Args>(args)), ...);
	tag << FIELD_TAG_RIGHT_ENCLOSER;

	return tag.str();

}

#endif
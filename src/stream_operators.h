#ifndef __STREAM_OPERATORS_H__
#define __STREAM_OPERATORS_H__

#include "reflection_utils.h"
#include "tools.h"
#include <ostream>
#include <vector>

/// <summary>
/// output stream operator for vectors.
/// </summary>
/// <typeparam name="T">type of the vector</typeparam>
/// <param name="os">output stream</param>
/// <param name="v">vector object</param>
/// <returns>output stream</returns>
template <class T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& v)
{
	for (auto ii = v.begin(); ii != v.end(); ++ii)
	{
		os << BuildTypeTagForStreamableObject<T>();
		os << GetStreamableObject(*ii);
	}
	return os;
}

/// <summary>
/// input stream operator for vectors.
/// </summary>
/// <typeparam name="T">type of the vector</typeparam>
/// <param name="is">input stream</param>
/// <param name="v">vector object</param>
/// <returns>input stream</returns>
template <class T>
std::istream& operator>>(std::istream& is, std::vector<T>& v)
{
	//if the stream is not in a valid state return
	if (is.fail())
		return is;

	//clear all elements in vector
	v.clear();

	//get vector string
	std::string vec_string{};
	if (!GetNextEnclosedString(is, vec_string, { FIELD_LEFT_ENCLOSER, FIELD_RIGHT_ENCLOSER }))
	{
		is.setstate(std::ios_base::badbit);
		return is;
	}

	//in case of empty vector string
	if (vec_string.empty())
		return is;

	std::stringstream vec_string_stream{ vec_string };
	T element{};
	while (GetObjectFromStream(element, vec_string_stream))
	{
		//if any value of the vector stream is not correct it will put the stream in an error state
		if (vec_string_stream.fail())
		{
			is.setstate(vec_string_stream.rdstate());
			return is;
		}
		v.push_back(element);
	}
	return is;
}

/// <summary>
/// output stream operator for enum types. Uses SFINAE technique for excluding
/// other types than enum. This operator overload is specifically to be used
/// with enum types.
/// </summary>
/// <typeparam name="T">Type</typeparam>
/// <param name="s">output stream</param>
/// <param name="t">enum object</param>
/// <returns>output stream</returns>
template <typename T>
typename std::enable_if<std::is_enum<T>::value, std::ostream&>::type&
operator<<(std::ostream& s, const T& t)
{
	return s << static_cast<typename std::underlying_type<T>::type>(t);
}

/// <summary>
/// input stream operator for enum types. Uses SFINAE technique for excluding
/// other types than enum. This operator overload is specifically to be used
/// with enum types.
/// </summary>
/// <typeparam name="T">Type</typeparam>
/// <param name="s">input stream</param>
/// <param name="t">enum object</param>
/// <returns>input stream</returns>
template <typename T>
typename std::enable_if<std::is_enum<T>::value, std::istream&>::type&
operator>>(std::istream& s, T& t)
{
	return s >> reinterpret_cast<typename std::underlying_type<T>::type&>(t);
}

#endif
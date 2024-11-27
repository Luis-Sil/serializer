#ifndef __REFLECTION_UTILS_H__
#define __REFLECTION_UTILS_H__

#include <string_view>
#include <array>
#include <vector>

/// <summary>
/// type traits for vector. Checks wether the type T is an std::vector or not at compile time
/// </summary>
/// <typeparam name="T">type to check</typeparam>
template<typename T> 
struct is_vector 
{ 
    using type = T;
    constexpr static bool value = false; 
};

template<typename T> 
struct is_vector<std::vector<T>> 
{ 
    using type = T;
    constexpr static bool value = true; 
};

template< typename T>
inline constexpr bool is_vector_v = is_vector<T>::value;

/// <summary>
/// transforms a type into a string at compile time. This code is compiler dependent, i.e., 
/// __FUNCSIG__ represents types differently accordingly to the compiler. Further processing 
/// can be done on vector, class and string types' names by using the tools inside namespace Detail.
/// This tool is designated to be used by invoking type_name<T> and not the func<T>() directly.
/// </summary>
/// <typeparam name="T">Type to be turned into string</typeparam>
/// <returns>string representing the type name</returns>
template <typename T>
constexpr std::string_view func()
{
    std::string_view signature{__FUNCSIG__};
    return std::string_view(signature.data() + 79, signature.size() - 79 - 7);
}

template <typename T>
constexpr auto type_name = func<T>();

/// <summary>
/// searches values by key in an array of pairs. This search happens at compile time.
/// The key must be a comparable type, otherwise it will not work.
/// </summary>
/// <typeparam name="U">key type</typeparam>
/// <typeparam name="T">value type</typeparam>
/// <param name="array">array of pairs of keys and values</param>
/// <param name="key">key to be used in the search</param>
/// <returns>i: index of array where the key matches. If it no match is found, return the array size.</returns>
template <typename U, typename T, size_t size>
constexpr auto FindInArray(const std::array<std::pair<U, T>, size> &array, const U &key)
{
    size_t i{};
    while (i < array.size())
    {
        if (array[i].first == key)
            return i;
        i++;
    }
    return i;
}

#endif
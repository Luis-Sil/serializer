#include "tools.h"

bool GetNextEnclosedString(std::istream& stream, std::string& str, const std::pair<std::string, std::string>& enclosers)
{
	if (!str.empty())
		str.clear();

	std::vector<std::string> leftEnclosers{}, rightEnclosers{};
	std::string tmp{};

	stream >> tmp;
	if (tmp != enclosers.first)
		return false;

	leftEnclosers.push_back(tmp);
	while (true)
	{
		stream >> tmp;
		if (tmp == enclosers.first) leftEnclosers.push_back(tmp);
		if (tmp == enclosers.second) rightEnclosers.push_back(tmp);

		if (leftEnclosers.size() == rightEnclosers.size())
			break;

		str.append(tmp);
		str.push_back(' ');

		//if the stream reaches its end without finding the left encloser
		if (stream.eof() && tmp != enclosers.second)
		{
			//matching end was not found
			return false;
		}
	}

	if (!str.empty())
		str.pop_back();//remove last inserted space

	return true;
}

bool EraseNextEnclosedString(std::string& str, const std::pair<char, char>& enclosers, size_t npos)
{
	std::string leftEnclosers{}, rightEnclosers{};

	std::string::iterator firstItr{ std::next(str.begin(), npos) }, secondItr{ std::next(str.begin(), npos) };

	//increment the string iterators while the first encloser is not found
	while (*firstItr != enclosers.first)
	{
		firstItr++;
		secondItr++;
	}

	do
	{
		if (*secondItr == enclosers.first)
			leftEnclosers.push_back(*secondItr);

		if (*secondItr == enclosers.second)
			rightEnclosers.push_back(*secondItr);

		secondItr++;

	} while ((leftEnclosers.size() != rightEnclosers.size()) && secondItr != str.end());

	//in the case the stream end was reached and enclosers were not matched
	if (leftEnclosers.size() != rightEnclosers.size())
		return false;

	//extract the string
	str.erase(firstItr, secondItr);

	return true;
}